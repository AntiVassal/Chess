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
	this->cube = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	this->cube->SetRelativeScale3D(boundsColumn);
	this->SetRootComponent(this->cube);
	this->bReplicates = true;
	this->SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AColumn::BeginPlay()
{
	Super::BeginPlay();
	//Спрятать клетки с начала игры
	this->setVisible(false);
}

// Called every frame
void AColumn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AColumn::setVisible_Implementation(bool isVisible) {
	this->cube->SetVisibility(isVisible);
}

void AColumn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AColumn, rowPosition);
	DOREPLIFETIME(AColumn, columnPosition);
}
int32 AColumn::getRowPosition() const {
	return this->rowPosition;
}
int32 AColumn::getColumnPosition()const {
	return this->columnPosition;
}
void AColumn::initialize_Implementation(int32 row, int32 column) {
	//Сохранить столбец и рядок клетки
	this->rowPosition = row;
	this->columnPosition = column;
}