// Fill out your copyright notice in the Description page of Project Settings.


#include "Column.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
AColumn::AColumn()
{
	//Размер клетки
	const int32 sizeColumn = 118.0f;
	//Границы клетки
	FVector boundsColumn = FVector(sizeColumn * 0.02f, sizeColumn * 0.02f, 0.01f);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->CubeMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	this->CubeMesh->SetRelativeScale3D(boundsColumn);
	this->SetRootComponent(this->CubeMesh);
	this->bReplicates = true;
	this->SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AColumn::BeginPlay()
{
	Super::BeginPlay();
	//Спрятать клетки с начала игры
	this->SetVisible(false);
}

// Called every frame
void AColumn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AColumn::SetVisible_Implementation(bool IsVisible) {
	this->CubeMesh->SetVisibility(IsVisible);
}

void AColumn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AColumn, RowPosition);
	DOREPLIFETIME(AColumn, ColumnPosition);
}
int32 AColumn::GetRowPosition() const {
	return this->RowPosition;
}
int32 AColumn::GetColumnPosition()const {
	return this->ColumnPosition;
}
void AColumn::Initialize_Implementation(int32 Row, int32 Column) {
	//Сохранить столбец и рядок клетки
	this->RowPosition = Row;
	this->ColumnPosition = Column;
}