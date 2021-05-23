// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnFigure.h"
#include "../Board.h"
#include "../ChessPawn.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "../Moves/PawnForwardOneStep.h"
#include "../Moves/PawnForwardTwoSteps.h"
#include "../Moves/PawnLeftDiagonal.h"
#include "../Moves/PawnRightDiagonal.h"
#include "../Moves/PawnLeftTake.h"
#include "../Moves/PawnRightTake.h"
APawnFigure::APawnFigure() {
	//Движение на одну клетку вперёд
	this->RegisterMove(this->CreateDefaultSubobject<UPawnForwardOneStep>(TEXT("ForwardOneStep")));
	//Движение на две клетки вперёд
	this->RegisterMove(this->CreateDefaultSubobject<UPawnForwardTwoSteps>(TEXT("ForwardTwoSteps")));
	//Взять фигуру по диагонали
	this->RegisterMove(this->CreateDefaultSubobject<UPawnLeftDiagonal>(TEXT("LeftDiagonal")));
	this->RegisterMove(this->CreateDefaultSubobject<UPawnRightDiagonal>(TEXT("RightDiagonal")));
	//Взять пешку, ступив на перепрыгнувшую клетку
	this->RegisterMove(this->CreateDefaultSubobject<UPawnLeftTake>(TEXT("LeftTake")));
	this->RegisterMove(this->CreateDefaultSubobject<UPawnRightTake>(TEXT("RightTake")));
}
float APawnFigure::GetPower(int8 Row, int8 Column) const {
	if (this->GetColor() == EColorFigure::BLACK) {
		Row = 7 - Row;
	}
	return 10.0f + PowerMatrix[Row][Column];
}
void APawnFigure::AnimateMove_Implementation(UMoveFigure* Move) {
	ABoard* Board = this->GetBoard();
	EColorFigure ColorFigure = this->GetColor();
	if (!Board->IsSimulated()) {
		auto Info = Move->GetFigureInfoAfterMoving();
		//Выполняем ход
		Super::AnimateMove_Implementation(Move);
		//Если пешка достигла последнего рядка, позволяем игроку выбрать фигуру на замену
		if (Info.Row == 7 && ColorFigure == EColorFigure::WHITE ||
			Info.Row == 0 && ColorFigure == EColorFigure::BLACK) {
			AChessPawn* Pawn = Board->GetPlayerPawn(ColorFigure);
			Pawn->OnPawnEndPath(Info.Row, Info.Column);
			this->Destroy();
			Move->FinishMove();
		}
	}
}