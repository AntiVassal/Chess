// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnLeftDiagonal.h"
#include "../Figure.h"
bool UPawnLeftDiagonal::isMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::isMoving()) {
		return false;
	}
	//По диагонали пешка может только бить
	return this->getDestroyFigure() != nullptr && this->getDestroyFigure()->getDirection() != this->getFigure()->getDirection();
}
int8 UPawnLeftDiagonal::toColumn() const {
	return this->getColumn() - 1;
}
int8 UPawnLeftDiagonal::toRow() const {
	return this->getRow() + (this->getFigure()->getDirection() == DirectionFigure::WHITE ? 1 : -1);
}