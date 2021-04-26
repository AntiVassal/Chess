// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveFigure.h"
#include "King.h"
#include "Board.h"

bool UMoveFigure::isMoving() {
	//Проверка на выход за пределы доски
	auto column = this->toColumn();
	auto row = this->toRow();
	if (column < 0 || column >= 8 || row < 0 || row >= 8) {
		return false;
	}
	//Проверяем не приведёт ли текущий ход к мату
	bool isMove = true;
	if (!this->getFigure()->getBoard()->isSimulated()) {
		//Включаем симуляцию
		this->getFigure()->getBoard()->startSimulation();
		if (this->isMoving()) {
			//Если ход возможен, то выполняем его
			this->move();
			//Проверяем не привёл ли ход к шаху
			isMove =!this->getFigure()->getBoard()->getKing(this->getFigure()->getDirection())->isCheck();
			//Откатываем состояние доски
			this->rollback();
		}
		//Останавливаем симуляцию
		this->getFigure()->getBoard()->stopSimulation();
		return isMove;
	}
	return isMove;
}
AFigure* UMoveFigure::getDestroyFigure() const {
	return this->getFigure()->getBoard()->getFigure(this->toRow(), this->toColumn());
}
void UMoveFigure::move(){
	this->getFigure()->getBoard()->moveFigure(this);
}
void UMoveFigure::rollback() {
	this->getFigure()->getBoard()->rollback();
}
int8 UMoveFigure::toColumn()const {
	return 0;
}
int8 UMoveFigure::toRow()const {
	return 0;
}
int8 UMoveFigure::getRow() const {
	return this->getFigure()->getBoard()->getRow(this->getFigure());
}
int8 UMoveFigure::getColumn() const {
	return this->getFigure()->getBoard()->getColumn(this->getFigure());
}
AFigure* UMoveFigure::getFigure() const {
	return this->_figure;
}
void UMoveFigure::initialzie(class AFigure* figure) {
	this->_figure = figure;
}
void UMoveFigure::finishMove() {
	this->getFigure()->getBoard()->togleNextMove();
}