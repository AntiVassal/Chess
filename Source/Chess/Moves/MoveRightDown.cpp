// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveRightDown.h"
#include "../Figure.h"
#include "../Board.h"
void UMoveRightDown::setCount(int8 count) {
	this->_count = count;
}
bool UMoveRightDown::isMoving() {
	//ѕровер€ем, не приведЄт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::isMoving()) {
		return false;
	}
	//≈сли между фигурой и клеткой назначени€ есть другие фигуры, то ход невозможен
	for (int8 i = 1; i < this->_count; ++i) {
		auto row = this->getRow() - i;
		auto column = this->getColumn() + i;
		auto figure = this->getFigure()->getBoard()->getFigure(row, column);
		if (figure != nullptr) {
			return false;
		}
	}
	//’од возможен только если клетка назначени€ пуста, или там находитс€ фигура, которую можно съесть
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveRightDown::toColumn() const {
	return this->getColumn() + this->_count;
}
int8 UMoveRightDown::toRow() const {
	return this->getRow() - this->_count;
}