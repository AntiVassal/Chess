// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Figures/Figure.h"
#include "ChessPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Column.h"
#include "Figures/King.h"
#include "AIChessPawn.h"
#include "Moves/MoveFigure.h"
// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicates = true;
	this->BoardMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardStaticMesh"));
	this->SetRootComponent(this->BoardMesh);
	//Первыми всегда ходят белые
	this->NextMove = EColorFigure::WHITE;
	//По умолчанию игра идёт по сети
	this->bAIPlayer = false;
	//Создание игрового поля
	for (int32 i = 0; i < 8; ++i) {
		this->BoardState.Rows.Add(FBoardRow());
		for (int32 j = 0; j < 8; ++j) {
			this->BoardState.Rows[i].Columns.Add(FBoardColumn());
		}
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	//Заполнение игрового поля происходит только на сервере
	if (this->HasAuthority()) {
		UWorld* World = this->GetWorld();
		if (World != nullptr) {
			for (int32 i = 0; i < 8; ++i) {
				//Просчёт расположения клеток игровой доски
				FVector forwardVector = (FVector::ForwardVector * i - FVector::ForwardVector * 4) * SizeColumn + 
					FVector::ForwardVector * SizeColumn / 2;
				for (int32 j = 0; j < 8; ++j) {
					FVector rightOffset = (FVector::RightVector * j - FVector::RightVector * 4) * SizeColumn +
						FVector::RightVector * SizeColumn / 2;
					AColumn* Column = World->SpawnActor<AColumn>(this->ColumnActor,
						rightOffset + forwardVector + this->GetActorLocation(), FRotator());
					Column->Initialize(i, j);
					this->Columns.Add(Column);
				}
			}
		}
		FRotator ForwardRotation(0.0f, 270, 0.0f);
		FRotator BackwardRotation(0.0f, 90.0f, 0.0f);
		for (int32 i = 0; i < 8; ++i) {
			//Спавн пешек
			this->SpawnFigure(this->PawnWhite, 1, i, ForwardRotation);
			this->SpawnFigure(this->PawnBlack, 6, i, BackwardRotation);
			if (i == 0 || i == 7) {
				//Спавн башен
				this->SpawnFigure(this->RockWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->RockBlack, 7, i, BackwardRotation);
			}
			else if (i == 1 || i == 6) {
				//Спавн коней
				this->SpawnFigure(this->KnightWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->KnightBlack, 7, i, BackwardRotation);
			}
			else if (i == 2 || i == 5) {
				//Спавн офицеров
				this->SpawnFigure(this->BishopWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->BishopBlack, 7, i, BackwardRotation);
			}
			else if (i == 3) {
				//Спавн ферзей
				this->SpawnFigure(this->QueenWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->QueenBlack, 7, i, BackwardRotation);
			}
			else if (i == 4) {
				//Спавн королей
				this->SpawnFigure(this->KingWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->KingBlack, 7, i, BackwardRotation);
			}
		}
	}
}
void ABoard::SpawnFigure(UClass* Figure, int32 Row, int32 Column, FRotator Rotator) {
	UWorld* World = this->GetWorld();
	if (World != nullptr && Figure != nullptr) {
		//Размещаем фигуру на доске
		AFigure* FigureActor = World->SpawnActor<AFigure>(Figure,
			this->Columns[Row * 8 + Column]->GetActorLocation() + this->GetActorLocation(),
			Rotator);
		FigureActor->Initialize(this);
		//Если в этой клетке уже присутствует фигура, уничтожаем её
		if (this->BoardState.Rows[Row].Columns[Column].Figure != nullptr) {
			this->BoardState.Rows[Row].Columns[Column].Figure->Destroy();
		}
		//Сохраняем указатель на фигуру в клетку
		this->BoardState.Rows[Row].Columns[Column].Figure = FigureActor;
		//Если спавниться король, то сохраняем его для дополнительной логики
		if (Figure == this->KingWhite) {
			this->WhiteKingPointer = Cast<AKing>(FigureActor);
		} else if (Figure == this->KingBlack) {
			this->BlackKingPointer = Cast<AKing>(FigureActor);
		}
	}
}
// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABoard::DisplayMoves_Implementation(const TArray<UMoveFigure*>& Moves) {
	//Сначала прячем все отображённые ходы
	this->HideMoves();
	//Перебираем все возможные ходы
	for (UMoveFigure* Move : Moves) {
		//Получаем клетку, в которой окажеться фигура, после выполнения хода
		FFigureInfo Info = Move->GetFigureInfoAfterMoving();
		AColumn* Column = this->GetColumn(Info.Row, Info.Column);
		//Подсвечиваем клетку
		Column->SetVisible(true);
	}
}
void ABoard::HideMoves_Implementation() {
	//Перебор всех клеток и снятие видимости
	for (AColumn* Column : this->Columns) {
		if (Column != nullptr) {
			Column->SetVisible(false);
		}
	}
}
void ABoard::InitializePawn_Implementation(AChessPawn* Pawn) {
	//Первый подключившийся игрок будет белым
	if (this->WhitePlayer == nullptr) {
		this->WhitePlayer = Pawn;
		Pawn->ColorSide = EColorFigure::WHITE;
		Pawn->OnDirectionReplicated();
		//Если включена игра против ИИ, то спавним Pawn, в котором реализована логика ИИ
		if (this->bAIPlayer) {
			this->GetWorld()->SpawnActor(AAIChessPawn::StaticClass());
		}
	}
	else if (this->BlackPlayer == nullptr) {
		// Второй подключившийся игрок - чёрный
		this->BlackPlayer = Pawn;
		Pawn->ColorSide = EColorFigure::BLACK;
		Pawn->OnDirectionReplicated();
	}
}
void ABoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABoard, Columns);
	DOREPLIFETIME(ABoard, NextMove);
	DOREPLIFETIME(ABoard, WhitePlayer);
	DOREPLIFETIME(ABoard, BlackPlayer);
	DOREPLIFETIME(ABoard, WhiteKingPointer);
	DOREPLIFETIME(ABoard, BlackKingPointer);
	DOREPLIFETIME(ABoard, BoardState);
}

AColumn* ABoard::GetColumn(int32 Row, int32 Column) const {
	if (Row < 0 || Row > 7 || Column < 0 || Column > 7) return nullptr;
	//Ячейки хранятся в одномерном масиве, поэтому считаем индекс и возвращаем нужную ячейку
	return this->Columns[Row * 8 + Column];
}
void ABoard::DestroyFigure_Implementation(AFigure* Figure) {
	//Если включена симуляция, то уничтожать фигуру не нужно
	if (!this->IsSimulated()) {
		Figure->Destroy();
	}
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			//Если включена симуляция, то сохраняем предыдущее состояние доски
			if (this->IsSimulated()) {
				if (this->SimulatedBoardState.Rows[i].Columns[j].Figure == Figure) {
					//Затираем указатель на фигуру, теперь фигура не будет учитываться при получении возможных ходов
					this->SimulatedBoardState.Rows[i].Columns[j].Figure = nullptr;
					break;
				}
			}else if (this->BoardState.Rows[i].Columns[j].Figure == Figure) {
				//Затираем указатель на фигуру, теперь фигура не будет учитываться при получении возможных ходов
				this->BoardState.Rows[i].Columns[j].Figure = nullptr;
				break;
			}
		}
	}
}
AFigure* ABoard::GetFigure(int32 Row, int32 Column) const {
	//Если включена симуляция, то возвращаем фигуру расположеную на последнем состоянии симулированной доски,
	//в противном случае возвращаем фигуру расположеную на реальной доске
	return this->IsSimulated() ?
		this->SimulatedBoardState.Rows[Row].Columns[Column].Figure :
		this->BoardState.Rows[Row].Columns[Column].Figure;
}
AChessPawn* ABoard::GetPlayerPawnNextMove() const {
	switch (this->NextMove) {
	case EColorFigure::WHITE:
		return this->WhitePlayer;
	case EColorFigure::BLACK:
		return this->BlackPlayer;
	}
	return nullptr;
}
void ABoard::TogleNextMove_Implementation() {
	//Если предыдущий ход был за белых, то ходят чёрные, в противном случае - белые
	switch (this->NextMove) {
	case EColorFigure::WHITE:
		this->NextMove = EColorFigure::BLACK;
		this->BlackPlayer->WhaitNextMove();
		break;
	case EColorFigure::BLACK:
		this->NextMove = EColorFigure::WHITE;
		this->WhitePlayer->WhaitNextMove();
		break;
	}
}
void ABoard::GetAllMoves(TArray<UMoveFigure*>& Moves, EColorFigure Color) {
	//Перебор всех фигур на доске и получение их возможных ходов
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			AFigure* Figure = this->GetFigure(i, j);
			if (Figure != nullptr && Figure->GetColor() == Color) {
				Figure->GetMoves(Moves);
			}
		}
	}
}
bool ABoard::IsSimulated() const {
	return this->bIsSimulated;
}
void ABoard::StartSimulation() {
	this->bIsSimulated = true;
	//При старте симуляции копируем текущее состояние доски в симуляцию
	this->SimulatedBoardState = this->BoardState;
	this->SimulatedPrevBoardStates.Empty();
}
void ABoard::StopSimulation() {
	this->bIsSimulated = false;
}
AKing* ABoard::GetKing(EColorFigure Direct) const {
	switch (Direct) {
	case EColorFigure::WHITE:
		return this->WhiteKingPointer;
	case EColorFigure::BLACK:
		return this->BlackKingPointer;
	}
	return nullptr;
}
AChessPawn* ABoard::GetPlayerPawn(EColorFigure Direct) const {
	switch (Direct) {
	case EColorFigure::WHITE:
		return this->WhitePlayer;
	case EColorFigure::BLACK:
		return this->BlackPlayer;
	}
	return nullptr;
}
float ABoard::GetPowerAllFigures(EColorFigure Color) const {
	float Result = 0.0f;
	//Перебор всех фигур на доске и подсчёт их веса
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			AFigure* figure = this->GetFigure(i, j);
			if (figure != nullptr && figure->GetColor() == Color) {
				Result += figure->GetPower(i, j);
			}
		}
	}
	return Result;
}
FFigureInfo ABoard::GetFigureInfo(const AFigure* Figure) const{
	FFigureInfo res;
	for(int32 i = 0; i < 8; ++i){
		for (int32 j = 0; j < 8; ++j) {
			if(this->IsSimulated()){
				if(this->SimulatedBoardState.Rows[i].Columns[j].Figure == Figure){
					res.Column = j;
					res.Row = i;
					res.CountMoves = this->SimulatedBoardState.Rows[i].Columns[j].CountMoves;
					return res;
				}
			}else{
				if(this->BoardState.Rows[i].Columns[j].Figure == Figure){
					res.Column = j;
					res.Row = i;
					res.CountMoves = this->BoardState.Rows[i].Columns[j].CountMoves;
					return res;
				}
			}
		}
	}
	return res;
}
void ABoard::MoveFigureOnBoard(UMoveFigure* Move) {
	//Если включена симуляция, то сохраняем предыдущее состояние доски
	if (this->IsSimulated()) {
		this->SimulatedPrevBoardStates.Add(this->SimulatedBoardState);
	}
	//Если при исполнении хода должна уничтожиться фигура, уничтожаем её
	if (Move->GetDestroyFigure() != nullptr) {
		FFigureInfo DestroyFigureInfo = this->GetFigureInfo(Move->GetDestroyFigure());
		if (this->IsSimulated()) {
			this->SimulatedBoardState.Rows[DestroyFigureInfo.Row].Columns[DestroyFigureInfo.Column].Figure = nullptr;
		}
		else {
			Move->GetDestroyFigure()->Destroy();
			this->BoardState.Rows[DestroyFigureInfo.Row].Columns[DestroyFigureInfo.Column].Figure = nullptr;
		}
	}
	//Перемещаем фигуру на реальной или симулированной доске, в зависимости од того, включена симуляция или нет.
	if (this->IsSimulated()) {
		FFigureInfo BeforeMoveFigureInfo = Move->GetFigureInfoBeforeMoving();
		FBoardColumn& PrevColumn = this->SimulatedBoardState.Rows[BeforeMoveFigureInfo.Row].Columns[BeforeMoveFigureInfo.Column];
		FFigureInfo AfterMoveFigureInfo = Move->GetFigureInfoAfterMoving();
		FBoardColumn& NextColumn = this->SimulatedBoardState.Rows[AfterMoveFigureInfo.Row].Columns[AfterMoveFigureInfo.Column];
		PrevColumn.Figure = nullptr;
		if (NextColumn.Figure == nullptr) {
			NextColumn.Figure = Move->GetFigure();
		}
		NextColumn.CountMoves = PrevColumn.CountMoves + 1;
		PrevColumn.CountMoves = 0;
	}
	else {
		FFigureInfo BeforeMoveFigureInfo = Move->GetFigureInfoBeforeMoving();
		FBoardColumn& PrevColumn = this->BoardState.Rows[BeforeMoveFigureInfo.Row].Columns[BeforeMoveFigureInfo.Column];
		FFigureInfo AfterMoveFigureInfo = Move->GetFigureInfoAfterMoving();
		FBoardColumn& NextColumn = this->BoardState.Rows[AfterMoveFigureInfo.Row].Columns[AfterMoveFigureInfo.Column];
		//Отрисовка анимации передвижения
		Move->GetFigure()->AnimateMove(Move);
		PrevColumn.Figure = nullptr;
		if (NextColumn.Figure == nullptr) {
			NextColumn.Figure = Move->GetFigure();
		}
		NextColumn.CountMoves = PrevColumn.CountMoves + 1;
		PrevColumn.CountMoves = 0;
	}
}
void ABoard::RollbackBoard() {
	//Откат хода возможен только в симуляции
	if (this->IsSimulated()) {
		this->SimulatedBoardState = this->SimulatedPrevBoardStates.Last();
		this->SimulatedPrevBoardStates.RemoveAt(this->SimulatedPrevBoardStates.Num() - 1);
	}
}
void ABoard::SetFigure(UClass* Figure, int8 Row, int8 Column, EColorFigure Direct) {
	FRotator forward(0.0f, 270, 0.0f);
	FRotator backward(0.0f, 90.0f, 0.0f);
	//Размежение фигуры на доске
	this->SpawnFigure(Figure, Row, Column, Direct == EColorFigure::WHITE ? forward : backward);
}
void ABoard::Lose(AChessPawn* Pawn) {
	//Сообщаем игроку, что он проиграл
	Pawn->Lose();
	switch (Pawn->ColorSide) {
	case EColorFigure::WHITE:
		//Сообщаем игроку, что он выиграл
		this->BlackPlayer->Win();
		break;
	case EColorFigure::BLACK:
		//Сообщаем игроку, что он выиграл
		this->WhitePlayer->Win();
		break;
	}
}