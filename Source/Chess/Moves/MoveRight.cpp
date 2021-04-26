// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveRight.h"
#include "../Figure.h"
#include "../Board.h"
void UMoveRight::setCount(int8 count) {
	this->_count = count;
}
bool UMoveRight::isMoving() {
	//ѕровер€ем, не приведЄт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::isMoving()) {
		return false;
	}
	auto row = this->getRow();
	auto column = this->getColumn() + 1;
	//≈сли между фигурой и клеткой назначени€ есть другие фигуры, то ход невозможен
	for (int8 i = column; i < column + this->_count - 1; ++i) {
		auto destFigure = this->getFigure()->getBoard()->getFigure(row, i);
		if (destFigure != nullptr) {
			return false;
		}
	}
	//’од возможен только если клетка назначени€ пуста, или там находитс€ фигура, которую можно съесть
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveRight::toColumn() const {
	return this->getColumn() + this->_count;
}
int8 UMoveRight::toRow() const {
	return this->getRow();
}