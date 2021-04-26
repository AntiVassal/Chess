// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKnight.h"
#include "../Figure.h"
bool UMoveKnight::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveKnight::toColumn() const {
	return this->getColumn() + this->_offsetColumn;
}
int8 UMoveKnight::toRow() const {
	return this->getRow() + this->_offsetRow;
}
void UMoveKnight::setOffset(int8 row, int8 column) {
	this->_offsetRow = row;
	this->_offsetColumn = column;
}