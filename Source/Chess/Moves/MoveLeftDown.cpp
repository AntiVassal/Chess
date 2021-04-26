// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLeftDown.h"
#include "../Figure.h"
#include "../Board.h"
void UMoveLeftDown::setCount(int8 count) {
	this->_count = count;
}
bool UMoveLeftDown::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	for (int8 i = 1; i < this->_count; ++i) {
		auto row = this->getRow() - i;
		auto column = this->getColumn() - i;
		auto figure = this->getFigure()->getBoard()->getFigure(row, column);
		if (figure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveLeftDown::toColumn() const {
	return this->getColumn() - this->_count;
}
int8 UMoveLeftDown::toRow() const {
	return this->getRow() - this->_count;
}

