// Fill out your copyright notice in the Description page of Project Settings.


#include "Figure.h"
#include "../Board.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "../Column.h"
#include "King.h"
#include "../Moves/MoveFigure.h"
// Sets default values
AFigure::AFigure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->FigureMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Figure"));
	this->SetRootComponent(this->FigureMesh);
	this->bReplicates = true;
	this->SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AFigure::BeginPlay()
{
	Super::BeginPlay();
	this->TargetMoveAnimation = this->GetActorLocation();
}

// Called every frame
void AFigure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->HasAuthority()) {
		//¬ыполн€ем анимацию перемещени€
		if (this->TargetMoveAnimation != this->GetActorLocation()) {
			this->SetActorLocation(
				FMath::VInterpTo(
					this->SourceMoveAnimation,
					this->TargetMoveAnimation,
					FMath::Clamp(this->TimeAnimationExecuted += DeltaTime, 0.0f, 1.0f),
					this->SpeedMoveFigure
				));
		}
		else if (this->bEndMove) {
			// огда анимаци€ завершена, сообщаем о завершении хода
			this->bEndMove = false;
			this->LastMove->FinishMove();
		}
	}
}
void AFigure::GetMoves(TArray<UMoveFigure*>& RefMoves) {
	//ѕолучаем все возможные ходы
	for (UMoveFigure* Move : this->Moves) {
		if (Move->IsValidMoving()) {
			RefMoves.Add(Move);
		}
	}
}
void AFigure::AnimateMove_Implementation(UMoveFigure* Move) {
	ABoard* Board = this->GetBoard();
	if (!Board->IsSimulated()) {
		//»нициализаци€ переменных дл€ правильного выполнени€ анимации
		FFigureInfo Info = Move->GetFigureInfoAfterMoving();
		AColumn* Column = Board->GetColumn(Info.Row, Info.Column);
		this->TargetMoveAnimation = Column->GetActorLocation();
		this->SourceMoveAnimation = this->GetActorLocation();
		this->TimeAnimationExecuted = 0;
		this->bEndMove = true;
		this->LastMove = Move;
	}
}
ABoard* AFigure::GetBoard() const {
	return this->BoardActor;
}
void AFigure::Initialize_Implementation(ABoard* Board) {
	this->BoardActor = Board;
}

void AFigure::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFigure, BoardActor);
}
EColorFigure AFigure::GetColor() const {
	return this->Color;
}
float AFigure::GetPower(int8 Row, int8 Column) const {
	return 0.0f;
}
void AFigure::RegisterMove(UMoveFigure* Move) {
	//—охранение возможного хода
	this->Moves.Add(Move);
	Move->Initialzie(this);
}