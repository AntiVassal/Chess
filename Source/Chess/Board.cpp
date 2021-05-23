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
	//������� ������ ����� �����
	this->NextMove = EColorFigure::WHITE;
	//�� ��������� ���� ��� �� ����
	this->bAIPlayer = false;
	//�������� �������� ����
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
	//���������� �������� ���� ���������� ������ �� �������
	if (this->HasAuthority()) {
		UWorld* World = this->GetWorld();
		if (World != nullptr) {
			for (int32 i = 0; i < 8; ++i) {
				//������� ������������ ������ ������� �����
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
			//����� �����
			this->SpawnFigure(this->PawnWhite, 1, i, ForwardRotation);
			this->SpawnFigure(this->PawnBlack, 6, i, BackwardRotation);
			if (i == 0 || i == 7) {
				//����� �����
				this->SpawnFigure(this->RockWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->RockBlack, 7, i, BackwardRotation);
			}
			else if (i == 1 || i == 6) {
				//����� �����
				this->SpawnFigure(this->KnightWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->KnightBlack, 7, i, BackwardRotation);
			}
			else if (i == 2 || i == 5) {
				//����� ��������
				this->SpawnFigure(this->BishopWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->BishopBlack, 7, i, BackwardRotation);
			}
			else if (i == 3) {
				//����� ������
				this->SpawnFigure(this->QueenWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->QueenBlack, 7, i, BackwardRotation);
			}
			else if (i == 4) {
				//����� �������
				this->SpawnFigure(this->KingWhite, 0, i, ForwardRotation);
				this->SpawnFigure(this->KingBlack, 7, i, BackwardRotation);
			}
		}
	}
}
void ABoard::SpawnFigure(UClass* Figure, int32 Row, int32 Column, FRotator Rotator) {
	UWorld* World = this->GetWorld();
	if (World != nullptr && Figure != nullptr) {
		//��������� ������ �� �����
		AFigure* FigureActor = World->SpawnActor<AFigure>(Figure,
			this->Columns[Row * 8 + Column]->GetActorLocation() + this->GetActorLocation(),
			Rotator);
		FigureActor->Initialize(this);
		//���� � ���� ������ ��� ������������ ������, ���������� �
		if (this->BoardState.Rows[Row].Columns[Column].Figure != nullptr) {
			this->BoardState.Rows[Row].Columns[Column].Figure->Destroy();
		}
		//��������� ��������� �� ������ � ������
		this->BoardState.Rows[Row].Columns[Column].Figure = FigureActor;
		//���� ���������� ������, �� ��������� ��� ��� �������������� ������
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
	//������� ������ ��� ����������� ����
	this->HideMoves();
	//���������� ��� ��������� ����
	for (UMoveFigure* Move : Moves) {
		//�������� ������, � ������� ��������� ������, ����� ���������� ����
		FFigureInfo Info = Move->GetFigureInfoAfterMoving();
		AColumn* Column = this->GetColumn(Info.Row, Info.Column);
		//������������ ������
		Column->SetVisible(true);
	}
}
void ABoard::HideMoves_Implementation() {
	//������� ���� ������ � ������ ���������
	for (AColumn* Column : this->Columns) {
		if (Column != nullptr) {
			Column->SetVisible(false);
		}
	}
}
void ABoard::InitializePawn_Implementation(AChessPawn* Pawn) {
	//������ �������������� ����� ����� �����
	if (this->WhitePlayer == nullptr) {
		this->WhitePlayer = Pawn;
		Pawn->ColorSide = EColorFigure::WHITE;
		Pawn->OnDirectionReplicated();
		//���� �������� ���� ������ ��, �� ������� Pawn, � ������� ����������� ������ ��
		if (this->bAIPlayer) {
			this->GetWorld()->SpawnActor(AAIChessPawn::StaticClass());
		}
	}
	else if (this->BlackPlayer == nullptr) {
		// ������ �������������� ����� - ������
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
	//������ �������� � ���������� ������, ������� ������� ������ � ���������� ������ ������
	return this->Columns[Row * 8 + Column];
}
void ABoard::DestroyFigure_Implementation(AFigure* Figure) {
	//���� �������� ���������, �� ���������� ������ �� �����
	if (!this->IsSimulated()) {
		Figure->Destroy();
	}
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			//���� �������� ���������, �� ��������� ���������� ��������� �����
			if (this->IsSimulated()) {
				if (this->SimulatedBoardState.Rows[i].Columns[j].Figure == Figure) {
					//�������� ��������� �� ������, ������ ������ �� ����� ����������� ��� ��������� ��������� �����
					this->SimulatedBoardState.Rows[i].Columns[j].Figure = nullptr;
					break;
				}
			}else if (this->BoardState.Rows[i].Columns[j].Figure == Figure) {
				//�������� ��������� �� ������, ������ ������ �� ����� ����������� ��� ��������� ��������� �����
				this->BoardState.Rows[i].Columns[j].Figure = nullptr;
				break;
			}
		}
	}
}
AFigure* ABoard::GetFigure(int32 Row, int32 Column) const {
	//���� �������� ���������, �� ���������� ������ ������������ �� ��������� ��������� �������������� �����,
	//� ��������� ������ ���������� ������ ������������ �� �������� �����
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
	//���� ���������� ��� ��� �� �����, �� ����� ������, � ��������� ������ - �����
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
	//������� ���� ����� �� ����� � ��������� �� ��������� �����
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
	//��� ������ ��������� �������� ������� ��������� ����� � ���������
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
	//������� ���� ����� �� ����� � ������� �� ����
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
	//���� �������� ���������, �� ��������� ���������� ��������� �����
	if (this->IsSimulated()) {
		this->SimulatedPrevBoardStates.Add(this->SimulatedBoardState);
	}
	//���� ��� ���������� ���� ������ ������������ ������, ���������� �
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
	//���������� ������ �� �������� ��� �������������� �����, � ����������� �� ����, �������� ��������� ��� ���.
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
		//��������� �������� ������������
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
	//����� ���� �������� ������ � ���������
	if (this->IsSimulated()) {
		this->SimulatedBoardState = this->SimulatedPrevBoardStates.Last();
		this->SimulatedPrevBoardStates.RemoveAt(this->SimulatedPrevBoardStates.Num() - 1);
	}
}
void ABoard::SetFigure(UClass* Figure, int8 Row, int8 Column, EColorFigure Direct) {
	FRotator forward(0.0f, 270, 0.0f);
	FRotator backward(0.0f, 90.0f, 0.0f);
	//���������� ������ �� �����
	this->SpawnFigure(Figure, Row, Column, Direct == EColorFigure::WHITE ? forward : backward);
}
void ABoard::Lose(AChessPawn* Pawn) {
	//�������� ������, ��� �� ��������
	Pawn->Lose();
	switch (Pawn->ColorSide) {
	case EColorFigure::WHITE:
		//�������� ������, ��� �� �������
		this->BlackPlayer->Win();
		break;
	case EColorFigure::BLACK:
		//�������� ������, ��� �� �������
		this->WhitePlayer->Win();
		break;
	}
}