// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "Board.h"
#include "MoveFigure.h"
#include "Moves/MoveLeft.h"
#include "Moves/MoveLeftUp.h"
#include "Moves/MoveUp.h"
#include "Moves/MoveRightUp.h"
#include "Moves/MoveRight.h"
#include "Moves/MoveRightDown.h"
#include "Moves/MoveDown.h"
#include "Moves/MoveLeftDown.h"
#include "Moves/MoveKingToRockLeft.h"
#include "Moves/MoveKingToRockRight.h"
bool AKing::isCheck() const {
	//�������� ��������� ���� ����������
	TArray<UMoveFigure*> lmoves;
	this->getBoard()->getAllMoves(lmoves,
		this->getDirection() == DirectionFigure::WHITE ? DirectionFigure::BLACK : DirectionFigure::WHITE);
	for (auto move : lmoves) {
		if (move->getDestroyFigure() == this) {
			//���� ���� �� ����� �������� �� ������, ����� ���
			return true;
		}
	}
	return false;
}

float AKing::getPower(int8 row, int8 column) const {
	if (this->getDirection() == DirectionFigure::BLACK) {
		row = 7 - row;
	}
	return 900.0f + powerMatrix[row][column];
}
AKing::AKing() {
	//�������� �����
	auto moveLeft = this->CreateDefaultSubobject<UMoveLeft>(TEXT("MoveLeft"));
	moveLeft->setCount(1);
	this->addMove(moveLeft);
	//�������� ����� � ���� �� ���������
	auto moveLeftUp = this->CreateDefaultSubobject<UMoveLeftUp>(TEXT("MoveLeftUp"));
	moveLeftUp->setCount(1);
	this->addMove(moveLeftUp);
	//�������� �����
	auto moveUp = this->CreateDefaultSubobject<UMoveUp>(TEXT("MoveUp"));
	moveUp->setCount(1);
	this->addMove(moveUp);
	//�������� ������ � ���� �� ���������
	auto moveRightUp = this->CreateDefaultSubobject<UMoveRightUp>(TEXT("MoveRightUp"));
	moveRightUp->setCount(1);
	this->addMove(moveRightUp);
	//�������� ������
	auto moveRight = this->CreateDefaultSubobject<UMoveRight>(TEXT("MoveRight"));
	moveRight->setCount(1);
	this->addMove(moveRight);
	//�������� ������ � ���� �� ���������
	auto moveRightDown = this->CreateDefaultSubobject<UMoveRightDown>(TEXT("MoveRightDown"));
	moveRightDown->setCount(1);
	this->addMove(moveRightDown);
	//�������� ����
	auto moveDown = this->CreateDefaultSubobject<UMoveDown>(TEXT("MoveDown"));
	moveDown->setCount(1);
	this->addMove(moveDown);
	//�������� ����� � ���� �� ���������
	auto moveLeftDown = this->CreateDefaultSubobject<UMoveLeftDown>(TEXT("MoveLeftDown"));
	moveLeftDown->setCount(1);
	this->addMove(moveLeftDown);
	//��������� � ����� ������
	this->addMove(this->CreateDefaultSubobject<UMoveKingToRockLeft>(TEXT("MoveKingToRockLeft")));
	//��������� � ������ ������
	this->addMove(this->CreateDefaultSubobject<UMoveKingToRockRight>(TEXT("MoveKingToRockRight")));
}