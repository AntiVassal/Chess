// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"
#include "Board.h"
#include "Moves/MoveUp.h"
#include "Moves/MoveDown.h"
#include "Moves/MoveLeft.h"
#include "Moves/MoveRight.h"
#include "Moves/MoveLeftUp.h"
#include "Moves/MoveRightUp.h"
#include "Moves/MoveRightDown.h"
#include "Moves/MoveLeftDown.h"
float AQueen::getPower(int8 row, int8 column) const {
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 90.0f + powerMatrix[row][column];
}
AQueen::AQueen() {
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
		//Ход влево и верх по диагонали на i клеток
		name = TEXT("MoveLeftUp");
		name.AppendInt(i);
		auto leftUp = this->CreateDefaultSubobject<UMoveLeftUp>(FName(name));
		leftUp->setCount(i);
		this->addMove(leftUp);
		//Ход вправо и верх по диагонали на i клеток
		name = TEXT("MoveRightUp");
		name.AppendInt(i);
		auto rightUp = this->CreateDefaultSubobject<UMoveRightUp>(FName(name));
		rightUp->setCount(i);
		this->addMove(rightUp);
		//Ход вправо и низ по диагонали на i клеток
		name = TEXT("MoveRightDown");
		name.AppendInt(i);
		auto rightDown = this->CreateDefaultSubobject<UMoveRightDown>(FName(name));
		rightDown->setCount(i);
		this->addMove(rightDown);
		//Ход влево и низ по диагонали на i клеток
		name = TEXT("MoveLeftDown");
		name.AppendInt(i);
		auto leftDown = this->CreateDefaultSubobject<UMoveLeftDown>(FName(name));
		leftDown->setCount(i);
		this->addMove(leftDown);
	}
}