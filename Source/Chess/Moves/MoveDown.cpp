// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveDown.h"
#include "../Figure.h"
#include "../Board.h"
void UMoveDown::setCount(int8 count) {
	this->_count = count;
}
bool UMoveDown::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	auto row = this->getRow() - 1;
	auto column = this->getColumn();
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	for (int8 i = row; i > row - this->_count + 1; --i) {
		auto destFigure = this->getFigure()->getBoard()->getFigure(i, column);
		if (destFigure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveDown::toColumn() const {
	return this->getColumn();
}
int8 UMoveDown::toRow() const {
	return this->getRow() - this->_count;
}