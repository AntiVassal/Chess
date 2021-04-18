// Fill out your copyright notice in the Description page of Project Settings.


#include "Figure.h"
#include "Board.h"

// Sets default values
AFigure::AFigure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->figure = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Figure"));
	this->SetRootComponent(this->figure);
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
	if (this->target != this->GetActorLocation()) {
		this->SetActorLocation(
			FMath::VInterpTo(
				this->source,
				this->target,
				FMath::Clamp(this->time += DeltaTime, 0.0f, 1.0f),
				Speed
			));
	}
}
TArray<FMove> AFigure::getMoves() const {
	return TArray<FMove>();
}
void AFigure::moveTo(int32 row, int32 column) {
	bool isValid = false;
	for (auto move : this->getMoves()) {
		if (move.toRow == row && move.toColumn == column) {
			isValid = true;
			break;
		}
	}
	if (isValid) {
		auto col = this->board->getColumn(row, column);
		this->target = col.location;
		this->source = this->GetActorLocation();
		this->time = 0;
		auto lfigure = this->board->getFigure(row, column);
		this->positionRow = row;
		this->positionColumn = column;
		if (lfigure != nullptr) {
			this->board->destroyFigure(lfigure);
		}
	}
}
int32 AFigure::getPositionRow() const {
	return this->positionRow;
}
int32 AFigure::getPositionColumn() const {
	return this->positionColumn;
}
ABoard* AFigure::getBoard() const {
	return this->board;
}
void AFigure::initialize(ABoard* lboard, int32 row, int32 column) {
	this->board = lboard;
	this->positionRow = row;
	this->positionColumn = column;
}