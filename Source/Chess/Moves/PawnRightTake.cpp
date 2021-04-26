// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnRightTake.h"
#include "../PawnFigure.h"
#include "../Board.h"
bool UPawnRightTake::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	auto pawn = Cast<APawnFigure>(this->getDestroyFigure());
	if (pawn == nullptr) {
		return false;
	}
	if (pawn->getDirection() == this->getFigure()->getDirection()) {
		return false;
	}
	//����� ����� ����� ������ �����, ���� ������ �� ������,
	//������� ������ ����� ������������ ��� ������ �� ��� ������ �����
	auto pawnRow = this->getFigure()->getBoard()->getRow(pawn);
	auto pawnCountMoves = this->getFigure()->getBoard()->getCountMoves(pawn);
	return pawnCountMoves == 1 && ((pawnRow == 3 && pawn->getDirection() == DirectionFigure::WHITE) ||
		(pawnRow == 4 && pawn->getDirection() == DirectionFigure::BLACK));
}
int8 UPawnRightTake::toColumn() const {
	return this->getColumn() + 1;
}
int8 UPawnRightTake::toRow() const {
	return this->getRow() + (this->getFigure()->getDirection() == DirectionFigure::WHITE ? 1 : -1);
}
AFigure* UPawnRightTake::getDestroyFigure() const {
	return this->getFigure()->getBoard()->getFigure(this->getRow(), this->toColumn());
}