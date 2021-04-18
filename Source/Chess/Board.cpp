// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Figure.h"
#include "ChessPawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicates = true;
	this->board = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardStaticMesh"));
	this->SetRootComponent(this->board);
	const int32 sizeColumn = 118.0f;
	FVector boundsColumn = FVector(sizeColumn * 0.02f, sizeColumn * 0.02f, 0.01f);
	for (int32 i = 0; i < 8; ++i) {
		FVector forwardVector = (FVector::ForwardVector * i - FVector::ForwardVector * 4) * sizeColumn * 2 + FVector::ForwardVector * sizeColumn;
		for (int32 j = 0; j < 8; ++j) {
			FColumnBoard column{ 0 };
			FVector rightOffset = (FVector::RightVector * j - FVector::RightVector * 4) * sizeColumn * 2 + FVector::RightVector * sizeColumn;
			FString name = TEXT("col_");
			name.AppendInt(i + 1);
			name.AppendInt(j + 1);
			auto col = this->CreateDefaultSubobject<UStaticMeshComponent>(FName(name));
			col->SetupAttachment(this->board);
			col->SetRelativeScale3D(boundsColumn);
			column.bounds = boundsColumn;
			col->SetRelativeLocation(rightOffset + forwardVector);
			col->SetVisibility(false);
			column.column = col;
			column.location = rightOffset + forwardVector;
			column.rowIndex = i;
			column.columnIndex = j;
			this->columns.Add(column);
		}
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	if (this->HasAuthority()) {
		FRotator forward(0.0f, 270, 0.0f);
		FRotator backward(0.0f, 90.0f, 0.0f);
		for (int32 i = 0; i < 8; ++i) {
			this->spawnFigure(this->pawnWhite, 1, i, forward);
			this->spawnFigure(this->pawnBlack, 6, i, backward);
			if (i == 0 || i == 7) {
				this->spawnFigure(this->rockWhite, 0, i, forward);
				this->spawnFigure(this->rockBlack, 7, i, backward);
			}
			else if (i == 1 || i == 6) {
				this->spawnFigure(this->knightWhite, 0, i, forward);
				this->spawnFigure(this->knightBlack, 7, i, backward);
			}
			else if (i == 2 || i == 5) {
				this->spawnFigure(this->bishopWhite, 0, i, forward);
				this->spawnFigure(this->bishopBlack, 7, i, backward);
			}
			else if (i == 3) {
				this->spawnFigure(this->queenWhite, 0, i, forward);
				this->spawnFigure(this->queenBlack, 7, i, backward);
			}
			else if (i == 4) {
				this->spawnFigure(this->kingWhite, 0, i, forward);
				this->spawnFigure(this->kingBlack, 7, i, backward);
			}
		}
	}
}
void ABoard::spawnFigure(UClass* figure, int32 row, int32 column, FRotator rotator) {
	auto world = this->GetWorld();
	if (world != nullptr && figure != nullptr) {
		auto figureActor = world->SpawnActor<AFigure>(figure,
			this->columns[row * 8 + column].location + this->GetActorLocation(),
			rotator);
		figureActor->initialize(this, row, column);
		this->figures.Add(figureActor);
	}
}
// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


#if WITH_EDITOR
void ABoard::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (!PropertyChangedEvent.Property)
		return;

	auto name = PropertyChangedEvent.Property->GetNameCPP();
}
#endif
FColumnBoard ABoard::getColumn(int32 row, int32 column) const {
	if (row < 0 || row > 7 || column < 0 || column > 7) return FColumnBoard();
	return this->columns[row * 8 + column];
}
void ABoard::selectFigure(int32 row, int32 column, DirectionFigure direction) {
	if (row < 0 || row > 7 || column < 0 || column > 7) return;
	if (this->selectedFigure != nullptr) {
		for (auto move : this->selectedFigure->getMoves()) {
			auto variant = this->getColumn(move.toRow, move.toColumn);
			variant.column->SetVisibility(false);
		}
	}
	auto figure = this->getFigure(row, column);
	if (figure != nullptr) {
		if (figure->direction == direction) {
			this->selectedFigure = figure;
			for (auto move : figure->getMoves()) {
				auto variant = this->getColumn(move.toRow, move.toColumn);
				variant.column->SetVisibility(true);
				variant.column->SetStaticMesh(this->cube);
				variant.column->SetMaterial(0, this->color);
			}
		} else {
			if (this->selectedFigure != nullptr) {
				for (auto move : this->selectedFigure->getMoves()) {
					if (row == move.toRow && column == move.toColumn) {
						this->moveFigureTo(this->selectedFigure, row, column);
						break;
					}
				}
			}
		}
	}
}
void ABoard::click(FVector point) {
	for (auto column : this->columns) {
		auto min = column.location - column.bounds / 0.02f;
		auto max = column.location + column.bounds / 0.02f;
		if (this->selectedFigure != nullptr && 
			point.X > min.X && point.X < max.X && point.Y > min.Y && point.Y < max.Y) {
			this->moveFigureTo(this->selectedFigure, column.rowIndex, column.columnIndex);
			break;
		}
	}
}
void ABoard::destroyFigure(AFigure* figure) {
	figure->Destroy();
	this->figures.Remove(figure);
}
void ABoard::moveFigureTo(AFigure* figure, int32 row, int32 col) {
	for (auto move : figure->getMoves()) {
		auto variant = this->getColumn(move.toRow, move.toColumn);
		variant.column->SetVisibility(false);
	}
	figure->moveTo(row, col);
	this->selectedFigure = nullptr;
}
AFigure* ABoard::getFigure(int32 row, int32 column) const {
	for (auto figure : this->figures) {
		if (figure->getPositionRow() == row && figure->getPositionColumn() == column) {
			return figure;
		}
	}
	return nullptr;
}
void ABoard::initializePawn_Implementation(AChessPawn* pawn) {
	if (this->white == nullptr) {
		this->white = pawn;
		pawn->direction = DirectionFigure::WHITE;
		pawn->onDirectionReplicated();
	} else if (this->black == nullptr) {
		this->black = pawn;
		pawn->direction = DirectionFigure::BLACK;
		pawn->onDirectionReplicated();
	}
}