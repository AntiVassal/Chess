// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveUp.h"
#include "../Figure.h"
#include "../Board.h"
void UMoveUp::setCount(int8 count) {
	this->_count = count;
}
bool UMoveUp::isMoving() {
	//ѕровер€ем, не приведЄт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::isMoving()) {
		return false;
	}
	auto row = this->getRow() + 1;
	auto column = this->getColumn();
	//≈сли между фигурой и клеткой назначени€ есть другие фигуры, то ход невозможен
	for (int8 i = row; i < row + this->_count - 1; ++i) {
		auto destFigure = this->getFigure()->getBoard()->getFigure(i, column);
		if (destFigure != nullptr) {
			return false;
		}
	}
	//’од возможен только если клетка назначени€ пуста, или там находитс€ фигура, которую можно съесть
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveUp::toColumn() const {
	return this->getColumn();
}
int8 UMoveUp::toRow() const {
	return this->getRow() + this->_count;
}