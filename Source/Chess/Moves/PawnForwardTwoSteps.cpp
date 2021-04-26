// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForwardTwoSteps.h"
#include "../Figure.h"
#include "../Board.h"
bool UPawnForwardTwoSteps::isMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::isMoving()) {
		return false;
	}
	//Мешка может ступить вперёд только если это первый её ход и две клетки перед ней пустые
	if (this->getFigure()->getBoard()->getFigure(
		this->getRow() + (this->getFigure()->getDirection() == DirectionFigure::WHITE ? 1 : -1),
		this->getColumn()) != nullptr) {
		return false;
	}
	return this->getDestroyFigure() == nullptr && this->getFigure()->getBoard()->getCountMoves(this->getFigure()) == 0;
}
int8 UPawnForwardTwoSteps::toColumn() const {
	return this->getColumn();
}
int8 UPawnForwardTwoSteps::toRow() const {
	return this->getFigure()->getDirection() == DirectionFigure::WHITE ? this->getRow() + 2 : this->getRow() - 2;
}