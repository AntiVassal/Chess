// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnFigure.h"
#include "Board.h"
#include "ChessPawn.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Moves/PawnForwardOneStep.h"
#include "Moves/PawnForwardTwoSteps.h"
#include "Moves/PawnLeftDiagonal.h"
#include "Moves/PawnRightDiagonal.h"
#include "Moves/PawnLeftTake.h"
#include "Moves/PawnRightTake.h"
APawnFigure::APawnFigure() {
	//Движение на одну клетку вперёд
	this->addMove(this->CreateDefaultSubobject<UPawnForwardOneStep>(TEXT("ForwardOneStep")));
	//Движение на две клетки вперёд
	this->addMove(this->CreateDefaultSubobject<UPawnForwardTwoSteps>(TEXT("ForwardTwoSteps")));
	//Взять фигуру по диагонали
	this->addMove(this->CreateDefaultSubobject<UPawnLeftDiagonal>(TEXT("LeftDiagonal")));
	this->addMove(this->CreateDefaultSubobject<UPawnRightDiagonal>(TEXT("RightDiagonal")));
	//Взять пешку, ступив на перепрыгнувшую клетку
	this->addMove(this->CreateDefaultSubobject<UPawnLeftTake>(TEXT("LeftTake")));
	this->addMove(this->CreateDefaultSubobject<UPawnRightTake>(TEXT("RightTake")));
}
float APawnFigure::getPower(int8 row, int8 column) const {
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 10.0f + powerMatrix[row][column];
}
void APawnFigure::moveTo_Implementation(UMoveFigure* move) {
	if (!this->getBoard()->isSimulated()) {
		auto row = move->toRow();
		auto column = move->toColumn();
		//Выполняем ход
		Super::moveTo_Implementation(move);
		//Если пешка достигла последнего рядка, позволяем игроку выбрать фигуру на замену
		if (row == 7 && this->getDirection() == DirectionFigure::WHITE ||
			row == 0 && this->getDirection() == DirectionFigure::BLACK) {
			auto pawn = this->getBoard()->getPawn(this->getDirection());
			pawn->pawnEndPath(row, column);
			this->Destroy();
			move->finishMove();
		}
	}
}