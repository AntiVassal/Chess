// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnLeftDiagonal.h"
#include "../Figure.h"
bool UPawnLeftDiagonal::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	//�� ��������� ����� ����� ������ ����
	return this->getDestroyFigure() != nullptr && this->getDestroyFigure()->getDirection() != this->getFigure()->getDirection();
}
int8 UPawnLeftDiagonal::toColumn() const {
	return this->getColumn() - 1;
}
int8 UPawnLeftDiagonal::toRow() const {
	return this->getRow() + (this->getFigure()->getDirection() == DirectionFigure::WHITE ? 1 : -1);
}