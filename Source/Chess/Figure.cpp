// Fill out your copyright notice in the Description page of Project Settings.


#include "Figure.h"
#include "Board.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Column.h"
#include "King.h"
#include "MoveFigure.h"
// Sets default values
AFigure::AFigure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->figure = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Figure"));
	this->SetRootComponent(this->figure);
	this->bReplicates = true;
	this->SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AFigure::BeginPlay()
{
	Super::BeginPlay();
	this->target = this->GetActorLocation();
}

// Called every frame
void AFigure::Tick(float DeltaTime)
{
	const float Speed = 1.0f;
	Super::Tick(DeltaTime);
	if (this->HasAuthority()) {
		//¬ыполн€ем анимацию перемещени€
		if (this->target != this->GetActorLocation()) {
			this->SetActorLocation(
				FMath::VInterpTo(
					this->source,
					this->target,
					FMath::Clamp(this->time += DeltaTime, 0.0f, 1.0f),
					Speed
				));
		}
		else if (this->isEndMove) {
			// огда анимаци€ завершена, сообщаем о завершении хода
			this->isEndMove = false;
			this->currentMove->finishMove();
		}
	}
}
void AFigure::getMoves(TArray<UMoveFigure*>& outMoves) {
	//ѕолучаем все возможные ходы
	for (auto move : this->moves) {
		if (move->isMoving()) {
			outMoves.Add(move);
		}
	}
}
void AFigure::moveTo_Implementation(UMoveFigure* move) {
	if (!this->getBoard()->isSimulated()) {
		//»нициализаци€ переменных дл€ правильного выполнени€ анимации
		auto col = this->board->getColumn(move->toRow(), move->toColumn());
		this->target = col->GetActorLocation();
		this->source = this->GetActorLocation();
		this->time = 0;
		this->isEndMove = true;
		this->currentMove = move;
	}
}
ABoard* AFigure::getBoard() const {
	return this->board;
}
void AFigure::initialize_Implementation(ABoard* aBoard) {
	this->board = aBoard;
}

void AFigure::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFigure, board);
}
DirectionFigure AFigure::getDirection() const {
	return this->direction;
}
float AFigure::getPower(int8 row, int8 column) const {
	return 0.0f;
}
void AFigure::addMove(UMoveFigure* move) {
	//—охранение возможного хода
	this->moves.Add(move);
	move->initialzie(this);
}