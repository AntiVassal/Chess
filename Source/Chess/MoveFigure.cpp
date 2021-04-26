// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveFigure.h"
#include "King.h"
#include "Board.h"

bool UMoveFigure::isMoving() {
	//�������� �� ����� �� ������� �����
	auto column = this->toColumn();
	auto row = this->toRow();
	if (column < 0 || column >= 8 || row < 0 || row >= 8) {
		return false;
	}
	//��������� �� ������� �� ������� ��� � ����
	bool isMove = true;
	if (!this->getFigure()->getBoard()->isSimulated()) {
		//�������� ���������
		this->getFigure()->getBoard()->startSimulation();
		if (this->isMoving()) {
			//���� ��� ��������, �� ��������� ���
			this->move();
			//��������� �� ����� �� ��� � ����
			isMove =!this->getFigure()->getBoard()->getKing(this->getFigure()->getDirection())->isCheck();
			//���������� ��������� �����
			this->rollback();
		}
		//������������� ���������
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