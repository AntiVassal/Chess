// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForwardOneStep.h"
#include "../Figure.h"
bool UPawnForwardOneStep::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	//����� ����� ������� ����� ������ ���� ������ ����� ��� ������
	return this->getDestroyFigure() == nullptr;
}
int8 UPawnForwardOneStep::toColumn() const {
	return this->getColumn();
}
int8 UPawnForwardOneStep::toRow() const {
	return this->getFigure()->getDirection() == DirectionFigure::WHITE ? this->getRow() + 1 : this->getRow() - 1;
}