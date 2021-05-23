// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "../Board.h"
#include "../Moves/MoveFigure.h"
#include "../Moves/MoveLeft.h"
#include "../Moves/MoveLeftUp.h"
#include "../Moves/MoveUp.h"
#include "../Moves/MoveRightUp.h"
#include "../Moves/MoveRight.h"
#include "../Moves/MoveRightDown.h"
#include "../Moves/MoveDown.h"
#include "../Moves/MoveLeftDown.h"
#include "../Moves/MoveKingToRockLeft.h"
#include "../Moves/MoveKingToRockRight.h"
bool AKing::IsCheck() const {
	//�������� ��������� ���� ����������
	TArray<UMoveFigure*> NextMoves;
	this->GetBoard()->GetAllMoves(NextMoves,
		this->GetColor() == EColorFigure::WHITE ? EColorFigure::BLACK : EColorFigure::WHITE);
	for (auto Move : NextMoves) {
		if (Move->GetDestroyFigure() == this) {
			//���� ���� �� ����� �������� �� ������, ����� ���
			return true;
		}
	}
	return false;
}

float AKing::GetPower(int8 Row, int8 Column) const {
	if (this->GetColor() == EColorFigure::BLACK) {
		Row = 7 - Row;
	}
	return 900.0f + PowerMatrix[Row][Column];
}
AKing::AKing() {
	//�������� �����
	UMoveLeft* MoveLeft = this->CreateDefaultSubobject<UMoveLeft>(TEXT("MoveLeft"));
	MoveLeft->SetLength(1);
	this->RegisterMove(MoveLeft);
	//�������� ����� � ���� �� ���������
	UMoveLeftUp* MoveLeftUp = this->CreateDefaultSubobject<UMoveLeftUp>(TEXT("MoveLeftUp"));
	MoveLeftUp->SetLength(1);
	this->RegisterMove(MoveLeftUp);
	//�������� �����
	UMoveUp* MoveUp = this->CreateDefaultSubobject<UMoveUp>(TEXT("MoveUp"));
	MoveUp->SetLength(1);
	this->RegisterMove(MoveUp);
	//�������� ������ � ���� �� ���������
	UMoveRightUp* MoveRightUp = this->CreateDefaultSubobject<UMoveRightUp>(TEXT("MoveRightUp"));
	MoveRightUp->SetLength(1);
	this->RegisterMove(MoveRightUp);
	//�������� ������
	UMoveRight* MoveRight = this->CreateDefaultSubobject<UMoveRight>(TEXT("MoveRight"));
	MoveRight->SetLength(1);
	this->RegisterMove(MoveRight);
	//�������� ������ � ���� �� ���������
	UMoveRightDown* MoveRightDown = this->CreateDefaultSubobject<UMoveRightDown>(TEXT("MoveRightDown"));
	MoveRightDown->SetLength(1);
	this->RegisterMove(MoveRightDown);
	//�������� ����
	UMoveDown* MoveDown = this->CreateDefaultSubobject<UMoveDown>(TEXT("MoveDown"));
	MoveDown->SetLength(1);
	this->RegisterMove(MoveDown);
	//�������� ����� � ���� �� ���������
	UMoveLeftDown* MoveLeftDown = this->CreateDefaultSubobject<UMoveLeftDown>(TEXT("MoveLeftDown"));
	MoveLeftDown->SetLength(1);
	this->RegisterMove(MoveLeftDown);
	//��������� � ����� ������
	this->RegisterMove(this->CreateDefaultSubobject<UMoveKingToRockLeft>(TEXT("MoveKingToRockLeft")));
	//��������� � ������ ������
	this->RegisterMove(this->CreateDefaultSubobject<UMoveKingToRockRight>(TEXT("MoveKingToRockRight")));
}