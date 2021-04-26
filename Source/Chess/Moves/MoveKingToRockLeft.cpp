// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKingToRockLeft.h"
#include "../Figure.h"
#include "../Board.h"
bool UMoveKingToRockLeft::isMoving() {
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
	auto rockFigure = this->getFigure()->getBoard()->getFigure(row, 0);
	if (rockFigure == nullptr) {
		return false;
	}
	auto rockMoves = this->getFigure()->getBoard()->getCountMoves(rockFigure);
	if (rockMoves > 0) {
		return false;
	}
	//Рокировка возможна только если между королём и башней нет других фигур
	for (int8 i = 1; i < column; ++i) {
		auto figure = this->getFigure()->getBoard()->getFigure(row, i);
		if (figure != nullptr) {
			return false;
		}
	}
	return true;
}
void UMoveKingToRockLeft::move() {
	auto row = this->getRow();
	auto column = this->getColumn();
	//Сначала перемещаем башню
	auto rockFigure = this->getFigure()->getBoard()->getFigure(row, 0);
	TArray<UMoveFigure*> moves;
	rockFigure->getMoves(moves);
	for (auto m : moves) {
		if (m->toRow() == row && m->toColumn() == column - 1) {
			m->move();
			break;
		}
	}
	//Перемещаем короля
	Super::move();
}
void UMoveKingToRockLeft::rollback() {
	//Откатываем перемещение короля
	Super::rollback();
	//Откатываем перемещение башни
	Super::rollback();
}
int8 UMoveKingToRockLeft::toColumn() const {
	return this->getColumn() - 2;
}
int8 UMoveKingToRockLeft::toRow() const {
	return this->getRow();
}
void UMoveKingToRockLeft::finishMove() {

}