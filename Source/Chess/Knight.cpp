// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "Board.h"
#include "Moves/MoveKnight.h"
float AKnight::getPower(int8 row, int8 column) const {
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 30.0f + powerMatrix[row][column];
}
AKnight::AKnight() {
	//’од на одну клетку вверх и две влево
	FName name = TEXT("Move1-2");
	auto move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(1, -2);
	this->addMove(move);
	//’од на две клетки вверх и одну влево
	name = TEXT("Move2-1");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(2, -1);
	this->addMove(move);
	//’од на две клетки вверх и одну вправо
	name = TEXT("Move21");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(2, 1);
	this->addMove(move);
	//’од на одну клетку вверх и две вправо
	name = TEXT("Move12");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(1, 2);
	this->addMove(move);
	//’од на одну клетку вниз и две вправо
	name = TEXT("Move-12");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(-1, 2);
	this->addMove(move);
	//’од на две клетки вниз и одну вправо
	name = TEXT("Move-21");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(-2, 1);
	this->addMove(move);
	//’од на две клетки вниз и одну влево
	name = TEXT("Move-2-1");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(-2, -1);
	this->addMove(move);
	//’од на одну клетку вниз и две влево
	name = TEXT("Move-1-2");
	move = this->CreateDefaultSubobject<UMoveKnight>(name);
	move->setOffset(-1, -2);
	this->addMove(move);
}