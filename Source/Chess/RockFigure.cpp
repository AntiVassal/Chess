// Fill out your copyright notice in the Description page of Project Settings.


#include "RockFigure.h"
#include "Board.h"
#include "Moves/MoveUp.h"
#include "Moves/MoveDown.h"
#include "Moves/MoveLeft.h"
#include "Moves/MoveRight.h"
ARockFigure::ARockFigure() {
	for (int8 i = 1; i < 8; ++i) {
		//Движение вверх на i клеток
		FString name = TEXT("MoveUp");
		name.AppendInt(i);
		auto moveUp = this->CreateDefaultSubobject<UMoveUp>(FName(name));
		moveUp->setCount(i);
		this->addMove(moveUp);
		//Движение вниз на i клеток
		name = TEXT("MoveDown");
		name.AppendInt(i);
		auto moveDown = this->CreateDefaultSubobject<UMoveDown>(FName(name));
		moveDown->setCount(i);
		this->addMove(moveDown);
		//Движение влево на i клеток
		name = TEXT("MoveLeft");
		name.AppendInt(i);
		auto moveLeft = this->CreateDefaultSubobject<UMoveLeft>(FName(name));
		moveLeft->setCount(i);
		this->addMove(moveLeft);
		//Движение вправо на i клеток
		name = TEXT("MoveRight");
		name.AppendInt(i);
		auto moveRight = this->CreateDefaultSubobject<UMoveRight>(FName(name));
		moveRight->setCount(i);
		this->addMove(moveRight);
	}
}
float ARockFigure::getPower(int8 row, int8 column) const {
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 50.0f + powerMatrix[row][column];
}