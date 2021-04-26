// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "Board.h"
#include "MoveFigure.h"
#include "Moves/MoveLeft.h"
#include "Moves/MoveLeftUp.h"
#include "Moves/MoveUp.h"
#include "Moves/MoveRightUp.h"
#include "Moves/MoveRight.h"
#include "Moves/MoveRightDown.h"
#include "Moves/MoveDown.h"
#include "Moves/MoveLeftDown.h"
#include "Moves/MoveKingToRockLeft.h"
#include "Moves/MoveKingToRockRight.h"
bool AKing::isCheck() const {
	//Получаем возможные ходы противника
	TArray<UMoveFigure*> lmoves;
	this->getBoard()->getAllMoves(lmoves,
		this->getDirection() == DirectionFigure::WHITE ? DirectionFigure::BLACK : DirectionFigure::WHITE);
	for (auto move : lmoves) {
		if (move->getDestroyFigure() == this) {
			//Если один из ходов целиться на короля, тогда шах
			return true;
		}
	}
	return false;
}

float AKing::getPower(int8 row, int8 column) const {
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 900.0f + powerMatrix[row][column];
}
AKing::AKing() {
	//Движение влево
	auto moveLeft = this->CreateDefaultSubobject<UMoveLeft>(TEXT("MoveLeft"));
	moveLeft->setCount(1);
	this->addMove(moveLeft);
	//Движение влево в верх по диагонали
	auto moveLeftUp = this->CreateDefaultSubobject<UMoveLeftUp>(TEXT("MoveLeftUp"));
	moveLeftUp->setCount(1);
	this->addMove(moveLeftUp);
	//Движение вверх
	auto moveUp = this->CreateDefaultSubobject<UMoveUp>(TEXT("MoveUp"));
	moveUp->setCount(1);
	this->addMove(moveUp);
	//Движение вправо в верх по диагонали
	auto moveRightUp = this->CreateDefaultSubobject<UMoveRightUp>(TEXT("MoveRightUp"));
	moveRightUp->setCount(1);
	this->addMove(moveRightUp);
	//движение вправо
	auto moveRight = this->CreateDefaultSubobject<UMoveRight>(TEXT("MoveRight"));
	moveRight->setCount(1);
	this->addMove(moveRight);
	//Движение вправо в вниз по диагонали
	auto moveRightDown = this->CreateDefaultSubobject<UMoveRightDown>(TEXT("MoveRightDown"));
	moveRightDown->setCount(1);
	this->addMove(moveRightDown);
	//Движение вниз
	auto moveDown = this->CreateDefaultSubobject<UMoveDown>(TEXT("MoveDown"));
	moveDown->setCount(1);
	this->addMove(moveDown);
	//Движение влево в вниз по диагонали
	auto moveLeftDown = this->CreateDefaultSubobject<UMoveLeftDown>(TEXT("MoveLeftDown"));
	moveLeftDown->setCount(1);
	this->addMove(moveLeftDown);
	//Рокировка с левой башней
	this->addMove(this->CreateDefaultSubobject<UMoveKingToRockLeft>(TEXT("MoveKingToRockLeft")));
	//Рокировка с правой башней
	this->addMove(this->CreateDefaultSubobject<UMoveKingToRockRight>(TEXT("MoveKingToRockRight")));
}