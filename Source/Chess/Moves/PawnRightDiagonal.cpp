// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnRightDiagonal.h"
#include "../Figure.h"
bool UPawnRightDiagonal::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	//�� ��������� ����� ����� ������ ����
	return this->getDestroyFigure() != nullptr && this->getDestroyFigure()->getDirection() != this->getFigure()->getDirection();
}
int8 UPawnRightDiagonal::toColumn() const {
	return this->getColumn() + 1;
}
int8 UPawnRightDiagonal::toRow() const {
	return this->getRow() + (this->getFigure()->getDirection() == DirectionFigure::WHITE ? 1 : -1);
}

