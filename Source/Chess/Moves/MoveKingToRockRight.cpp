// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKingToRockRight.h"
#include "../Figure.h"
#include "../Board.h"
bool UMoveKingToRockRight::isMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::isMoving()) {
		return false;
	}
	//Рокировка возможна только если король не разу не ходил
	auto countMoves = this->getFigure()->getBoard()->getCountMoves(this->getFigure());
	if (countMoves > 0) {
		return false;
	}
	auto row = this->getRow();
	auto column = this->getColumn();
	//Рокировка возможна только если башня не разу не ходила
	auto rockFigure = this->getFigure()->getBoard()->getFigure(row, 7);
	if (rockFigure == nullptr) {
		return false;
	}
	auto rockMoves = this->getFigure()->getBoard()->getCountMoves(rockFigure);
	if (rockMoves > 0) {
		return false;
	}
	//Рокировка возможна только если между королём и башней нет других фигур
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
	//Сначала перемещаем башню
	auto rockFigure = this->getFigure()->getBoard()->getFigure(row, 7);
	TArray<UMoveFigure*> moves;
	rockFigure->getMoves(moves);
	for (auto m : moves) {
		if (m->toRow() == row && m->toColumn() == column + 1) {
			m->move();
			break;
		}
	}
	//Перемещаем короля
	Super::move();
}
void UMoveKingToRockRight::rollback() {
	//Откатываем перемещение короля
	Super::rollback();
	//Откатываем перемещение башни
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