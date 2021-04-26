// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Figure.h"
#include "ChessPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Column.h"
#include "King.h"
#include "AIChessPawn.h"
#include "MoveFigure.h"
// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicates = true;
	this->boardMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardStaticMesh"));
	this->SetRootComponent(this->boardMesh);
	//Первыми всегда ходят белые
	this->nextMove = DirectionFigure::WHITE;
	//По умолчанию игра идёт по сети
	this->bIsAIPlayer = false;
	//Создание игрового поля
	for (int32 i = 0; i < 8; ++i) {
		this->board.rows.Add(FBoardRow());
		for (int32 j = 0; j < 8; ++j) {
			this->board.rows[i].columns.Add(FBoardColumn());
		}
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	//Заполнение игрового поля происходит только на сервере
	if (this->HasAuthority()) {
		auto world = this->GetWorld();
		const int32 sizeColumn = 118.0f;
		if (world != nullptr) {
			for (int32 i = 0; i < 8; ++i) {
				//Просчёт расположения клеток игровой доски
				FVector forwardVector = (FVector::ForwardVector * i - FVector::ForwardVector * 4) * sizeColumn * 2 + FVector::ForwardVector * sizeColumn;
				for (int32 j = 0; j < 8; ++j) {
					FVector rightOffset = (FVector::RightVector * j - FVector::RightVector * 4) * sizeColumn * 2 + FVector::RightVector * sizeColumn;
					auto column = world->SpawnActor<AColumn>(this->columnActor,
						rightOffset + forwardVector + this->GetActorLocation(), FRotator());
					column->initialize(i, j);
					this->columns.Add(column);
				}
			}
		}
		FRotator forward(0.0f, 270, 0.0f);
		FRotator backward(0.0f, 90.0f, 0.0f);
		for (int32 i = 0; i < 8; ++i) {
			//Спавн пешек
			this->spawnFigure(this->pawnWhite, 1, i, forward);
			this->spawnFigure(this->pawnBlack, 6, i, backward);
			if (i == 0 || i == 7) {
				//Спавн башен
				this->spawnFigure(this->rockWhite, 0, i, forward);
				this->spawnFigure(this->rockBlack, 7, i, backward);
			}
			else if (i == 1 || i == 6) {
				//Спавн коней
				this->spawnFigure(this->knightWhite, 0, i, forward);
				this->spawnFigure(this->knightBlack, 7, i, backward);
			}
			else if (i == 2 || i == 5) {
				//Спавн офицеров
				this->spawnFigure(this->bishopWhite, 0, i, forward);
				this->spawnFigure(this->bishopBlack, 7, i, backward);
			}
			else if (i == 3) {
				//Спавн ферзей
				this->spawnFigure(this->queenWhite, 0, i, forward);
				this->spawnFigure(this->queenBlack, 7, i, backward);
			}
			else if (i == 4) {
				//Спавн королей
				this->spawnFigure(this->kingWhite, 0, i, forward);
				this->spawnFigure(this->kingBlack, 7, i, backward);
			}
		}
	}
}
void ABoard::spawnFigure(UClass* figure, int32 row, int32 column, FRotator rotator) {
	auto world = this->GetWorld();
	if (world != nullptr && figure != nullptr) {
		//Размещаем фигуру на доске
		auto figureActor = world->SpawnActor<AFigure>(figure,
			this->columns[row * 8 + column]->GetActorLocation() + this->GetActorLocation(),
			rotator);
		figureActor->initialize(this);
		//Если в этой клетке уже присутствует фигура, уничтожаем её
		if (this->board.rows[row].columns[column].figure != nullptr) {
			this->board.rows[row].columns[column].figure->Destroy();
		}
		//Сохраняем указатель на фигуру в клетку
		this->board.rows[row].columns[column].figure = figureActor;
		//Если спавниться король, то сохраняем его для дополнительной логики
		if (figure == this->kingWhite) {
			this->whiteKing = Cast<AKing>(figureActor);
		} else if (figure == this->kingBlack) {
			this->blackKing = Cast<AKing>(figureActor);
		}
	}
}
// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABoard::displayMoves_Implementation(const TArray<UMoveFigure*>& moves) {
	//Сначала прячем все отображённые ходы
	this->hideMoves();
	//Перебираем все возможные ходы
	for (auto move : moves) {
		//Получаем клетку, в которой окажеться фигура, после выполнения хода
		auto col = this->getColumn(move->toRow(), move->toColumn());
		//Подсвечиваем клетку
		col->setVisible(true);
	}
}
void ABoard::hideMoves_Implementation() {
	//Перебор всех клеток и снятие видимости
	for (auto col : this->columns) {
		if (col != nullptr) {
			col->setVisible(false);
		}
	}
}
void ABoard::initializePawn_Implementation(AChessPawn* pawn) {
	//Первый подключившийся игрок будет белым
	if (this->white == nullptr) {
		this->white = pawn;
		pawn->direction = DirectionFigure::WHITE;
		pawn->onDirectionReplicated();
		//Если включена игра против ИИ, то спавним Pawn, в котором реализована логика ИИ
		if (this->bIsAIPlayer) {
			this->GetWorld()->SpawnActor(AAIChessPawn::StaticClass());
		}
	}
	else if (this->black == nullptr) {
		// Второй подключившийся игрок - чёрный
		this->black = pawn;
		pawn->direction = DirectionFigure::BLACK;
		pawn->onDirectionReplicated();
	}
}
void ABoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABoard, columns);
	DOREPLIFETIME(ABoard, nextMove);
	DOREPLIFETIME(ABoard, white);
	DOREPLIFETIME(ABoard, black);
	DOREPLIFETIME(ABoard, whiteKing);
	DOREPLIFETIME(ABoard, blackKing);
	DOREPLIFETIME(ABoard, board);
}

AColumn* ABoard::getColumn(int32 row, int32 column) const {
	if (row < 0 || row > 7 || column < 0 || column > 7) return nullptr;
	//Ячейки хранятся в одномерном масиве, поэтому считаем индекс и возвращаем нужную ячейку
	return this->columns[row * 8 + column];
}
void ABoard::destroyFigure_Implementation(AFigure* figure) {
	//Если включена симуляция, то уничтожать фигуру не нужно
	if (!this->isSimulated()) {
		figure->Destroy();
	}
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			//Если включена симуляция, то сохраняем предыдущее состояние доски
			if (this->isSimulated()) {
				if (this->simulatedBoard.rows[i].columns[j].figure == figure) {
					//Затираем указатель на фигуру, теперь фигура не будет учитываться при получении возможных ходов
					this->simulatedBoard.rows[i].columns[j].figure = nullptr;
					break;
				}
			}else if (this->board.rows[i].columns[j].figure == figure) {
				//Затираем указатель на фигуру, теперь фигура не будет учитываться при получении возможных ходов
				this->board.rows[i].columns[j].figure = nullptr;
				break;
			}
		}
	}
}
AFigure* ABoard::getFigure(int32 row, int32 column) const {
	//Если включена симуляция, то возвращаем фигуру расположеную на последнем состоянии симулированной доски,
	//в противном случае возвращаем фигуру расположеную на реальной доске
	return this->isSimulated() ?
		this->simulatedBoard.rows[row].columns[column].figure :
		this->board.rows[row].columns[column].figure;
}
AChessPawn* ABoard::getNextMovePawn() const {
	switch (this->nextMove) {
	case DirectionFigure::WHITE:
		return this->white;
	case DirectionFigure::BLACK:
		return this->black;
	}
	return nullptr;
}
void ABoard::togleNextMove_Implementation() {
	//Если предыдущий ход был за белых, то ходят чёрные, в противном случае - белые
	switch (this->nextMove) {
	case DirectionFigure::WHITE:
		this->nextMove = DirectionFigure::BLACK;
		this->black->whaitMove();
		break;
	case DirectionFigure::BLACK:
		this->nextMove = DirectionFigure::WHITE;
		this->white->whaitMove();
		break;
	}
}
void ABoard::getAllMoves(TArray<UMoveFigure*>& res, DirectionFigure direct) {
	//Перебор всех фигур на доске и получение их возможных ходов
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			auto figure = this->getFigure(i, j);
			if (figure != nullptr && figure->getDirection() == direct) {
				figure->getMoves(res);
			}
		}
	}
}
bool ABoard::isSimulated() const {
	return this->_isSimulated;
}
void ABoard::startSimulation() {
	this->_isSimulated = true;
	//При старте симуляции копируем текущее состояние доски в симуляцию
	this->simulatedBoard = this->board;
	this->simulatedPrevBoards.Empty();
}
void ABoard::stopSimulation() {
	this->_isSimulated = false;
}
AKing* ABoard::getKing(DirectionFigure direct) const {
	switch (direct) {
	case DirectionFigure::WHITE:
		return this->whiteKing;
	case DirectionFigure::BLACK:
		return this->blackKing;
	}
	return nullptr;
}
AChessPawn* ABoard::getPawn(DirectionFigure direct) const {
	switch (direct) {
	case DirectionFigure::WHITE:
		return this->white;
	case DirectionFigure::BLACK:
		return this->black;
	}
	return nullptr;
}
float ABoard::getPower(DirectionFigure direct) const {
	float res = 0.0f;
	//Перебор всех фигур на доске и подсчёт их веса
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			auto figure = this->getFigure(i, j);
			if (figure != nullptr && figure->getDirection() == direct) {
				res += figure->getPower(i, j);
			}
		}
	}
	return res;
}
int32 ABoard::getRow(const AFigure* figure) const {
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			//Если включена симуляция, то ищем фигуру в симулированной доске, иначе - в реальной
			if (this->isSimulated()) {
				if (this->simulatedBoard.rows[i].columns[j].figure == figure) {
					return i;
				}
			}
			else {
				if (this->board.rows[i].columns[j].figure == figure) {
					return i;
				}
			}
		}
	}
	return -1;
}
int32 ABoard::getColumn(const AFigure* figure)const {
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			//Если включена симуляция, то ищем фигуру в симулированной доске, иначе - в реальной
			if (this->isSimulated()) {
				if (this->simulatedBoard.rows[i].columns[j].figure == figure) {
					return j;
				}
			}
			else {
				if (this->board.rows[i].columns[j].figure == figure) {
					return j;
				}
			}
		}
	}
	return -1;
}
void ABoard::moveFigure(UMoveFigure* move) {
	//Если включена симуляция, то сохраняем предыдущее состояние доски
	if (this->isSimulated()) {
		this->simulatedPrevBoards.Add(this->simulatedBoard);
	}
	//Если при исполнении хода должна уничтожиться фигура, уничтожаем её
	if (move->getDestroyFigure() != nullptr) {
		auto destroyRow = this->getRow(move->getDestroyFigure());
		auto destroyColumn = this->getColumn(move->getDestroyFigure());
		if (destroyColumn != -1 && destroyRow != -1) {
			if (this->isSimulated()) {
				this->simulatedBoard.rows[destroyRow].columns[destroyColumn].figure = nullptr;
			}
			else {
				move->getDestroyFigure()->Destroy();
				this->board.rows[destroyRow].columns[destroyColumn].figure = nullptr;
			}
		}
	}
	//Перемещаем фигуру на реальной или симулированной доске, в зависимости од того, включена симуляция или нет.
	if (this->isSimulated()) {
		auto& prevColumn = this->simulatedBoard.rows[move->getRow()].columns[move->getColumn()];
		auto& nextColumn = this->simulatedBoard.rows[move->toRow()].columns[move->toColumn()];
		prevColumn.figure = nullptr;
		if (nextColumn.figure == nullptr) {
			nextColumn.figure = move->getFigure();
		}
		nextColumn.countMoves =	prevColumn.countMoves + 1;
		prevColumn.countMoves = 0;
	}
	else {
		auto& prevColumn = this->board.rows[move->getRow()].columns[move->getColumn()];
		auto& nextColumn = this->board.rows[move->toRow()].columns[move->toColumn()];
		//Отрисовка анимации передвижения
		move->getFigure()->moveTo(move);
		prevColumn.figure = nullptr;
		if (nextColumn.figure == nullptr) {
			nextColumn.figure = move->getFigure();
		}
		nextColumn.countMoves = prevColumn.countMoves + 1;
		prevColumn.countMoves = 0;
	}
}
void ABoard::rollback() {
	//Откат хода возможен только в симуляции
	if (this->isSimulated()) {
		this->simulatedBoard = this->simulatedPrevBoards.Last();
		this->simulatedPrevBoards.RemoveAt(this->simulatedPrevBoards.Num() - 1);
	}
}
int32 ABoard::getCountMoves(const class AFigure* figure) const {
	for (int32 i = 0; i < 8; ++i) {
		for (int32 j = 0; j < 8; ++j) {
			//Поиск фигуры на реальной или симулированной доске, в зависимости од того, включена симуляция или нет.
			if (this->isSimulated()) {
				if (this->simulatedBoard.rows[i].columns[j].figure == figure) {
					return this->simulatedBoard.rows[i].columns[j].countMoves;
				}
			}
			else {
				if (this->board.rows[i].columns[j].figure == figure) {
					return this->board.rows[i].columns[j].countMoves;
				}
			}
		}
	}
	return 0;
}
void ABoard::setFigure(UClass* figure, int8 row, int8 column, DirectionFigure direct) {
	FRotator forward(0.0f, 270, 0.0f);
	FRotator backward(0.0f, 90.0f, 0.0f);
	//Размежение фигуры на доске
	this->spawnFigure(figure, row, column, direct == DirectionFigure::WHITE ? forward : backward);
}
void ABoard::lose(AChessPawn* pawn) {
	//Сообщаем игроку, что он проиграл
	pawn->lose();
	switch (pawn->direction) {
	case DirectionFigure::WHITE:
		//Сообщаем игроку, что он выиграл
		this->black->win();
		break;
	case DirectionFigure::BLACK:
		//Сообщаем игроку, что он выиграл
		this->white->win();
		break;
	}
}