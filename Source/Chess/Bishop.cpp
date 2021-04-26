// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "Board.h"
#include "Moves/MoveLeftUp.h"
#include "Moves/MoveRightUp.h"
#include "Moves/MoveRightDown.h"
#include "Moves/MoveLeftDown.h"
float ABishop::getPower(int8 row, int8 column) const {
	//���� ������ ������, �� ������������� �������.
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 30.0f + powerMatrix[row][column];
}
ABishop::ABishop() {
	//���������� ���������� ������
	for (int8 i = 1; i < 8; ++i) {
		FString name = TEXT("MoveLeftUp");
		name.AppendInt(i);
		//��� ����� � ���� �� ��������� �� i ������
		auto leftUp = this->CreateDefaultSubobject<UMoveLeftUp>(FName(name));
		leftUp->setCount(i);
		this->addMove(leftUp);
		name = TEXT("MoveRightUp");
		name.AppendInt(i);
		//��� ������ � ���� �� ��������� �� i ������
		auto rightUp = this->CreateDefaultSubobject<UMoveRightUp>(FName(name));
		rightUp->setCount(i);
		this->addMove(rightUp);
		name = TEXT("MoveRightDown");
		name.AppendInt(i);
		//��� ������ � ��� �� ��������� �� i ������
		auto rightDown = this->CreateDefaultSubobject<UMoveRightDown>(FName(name));
		rightDown->setCount(i);
		this->addMove(rightDown);
		name = TEXT("MoveLeftDown");
		name.AppendInt(i);
		//��� ����� � ��� �� ��������� �� i ������
		auto leftDown = this->CreateDefaultSubobject<UMoveLeftDown>(FName(name));
		leftDown->setCount(i);
		this->addMove(leftDown);
	}
}