// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveUp.h"
#include "../Figure.h"
#include "../Board.h"
void UMoveUp::setCount(int8 count) {
	this->_count = count;
}
bool UMoveUp::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	auto row = this->getRow() + 1;
	auto column = this->getColumn();
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	for (int8 i = row; i < row + this->_count - 1; ++i) {
		auto destFigure = this->getFigure()->getBoard()->getFigure(i, column);
		if (destFigure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	auto destroyFigure = this->getDestroyFigure();
	return destroyFigure == nullptr || destroyFigure->getDirection() != this->getFigure()->getDirection();
}
int8 UMoveUp::toColumn() const {
	return this->getColumn();
}
int8 UMoveUp::toRow() const {
	return this->getRow() + this->_count;
}