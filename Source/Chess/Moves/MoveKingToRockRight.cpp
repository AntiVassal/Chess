// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKingToRockRight.h"
#include "../Figure.h"
#include "../Board.h"
bool UMoveKingToRockRight::isMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::isMoving()) {
		return false;
	}
	//��������� �������� ������ ���� ������ �� ���� �� �����
	auto countMoves = this->getFigure()->getBoard()->getCountMoves(this->getFigure());
	if (countMoves > 0) {
		return false;
	}
	auto row = this->getRow();
	auto column = this->getColumn();
	//��������� �������� ������ ���� ����� �� ���� �� ������
	auto rockFigure = this->getFigure()->getBoard()->getFigure(row, 7);
	if (rockFigure == nullptr) {
		return false;
	}
	auto rockMoves = this->getFigure()->getBoard()->getCountMoves(rockFigure);
	if (rockMoves > 0) {
		return false;
	}
	//��������� �������� ������ ���� ����� ������ � ������ ��� ������ �����
	for (int8 i = column + 1; i < 7; ++i) {
		auto figure = this->getFigure()->getBoard()->getFigure(row, i);
		if (figure != nullptr) {
			return false;
		}
	}
	return true;
}
void UMoveKingToRockRight::move() {
	auto row = this->getRow();
	auto column = this->getColumn();
	//������� ���������� �����
	auto rockFigure = this->getFigure()->getBoard()->getFigure(row, 7);
	TArray<UMoveFigure*> moves;
	rockFigure->getMoves(moves);
	for (auto m : moves) {
		if (m->toRow() == row && m->toColumn() == column + 1) {
			m->move();
			break;
		}
	}
	//���������� ������
	Super::move();
}
void UMoveKingToRockRight::rollback() {
	//���������� ����������� ������
	Super::rollback();
	//���������� ����������� �����
	Super::rollback();
}
int8 UMoveKingToRockRight::toColumn() const {
	return this->getColumn() + 2;
}
int8 UMoveKingToRockRight::toRow() const {
	return this->getRow();
}
void UMoveKingToRockRight::finishMove() {

}