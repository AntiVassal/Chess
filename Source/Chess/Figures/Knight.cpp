// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "../Board.h"
#include "../Moves/MoveKnight.h"
float AKnight::GetPower(int8 Row, int8 Column) const {
	if (this->GetColor() == EColorFigure::BLACK) {
		Row = 7 - Row;
	}
	return 30.0f + PowerMatrix[Row][Column];
}
AKnight::AKnight() {
	//��� �� ���� ������ ����� � ��� �����
	FName Name = TEXT("Move1-2");
	UMoveKnight* Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(1, -2);
	this->RegisterMove(Move);
	//��� �� ��� ������ ����� � ���� �����
	Name = TEXT("Move2-1");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(2, -1);
	this->RegisterMove(Move);
	//��� �� ��� ������ ����� � ���� ������
	Name = TEXT("Move21");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(2, 1);
	this->RegisterMove(Move);
	//��� �� ���� ������ ����� � ��� ������
	Name = TEXT("Move12");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(1, 2);
	this->RegisterMove(Move);
	//��� �� ���� ������ ���� � ��� ������
	Name = TEXT("Move-12");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(-1, 2);
	this->RegisterMove(Move);
	//��� �� ��� ������ ���� � ���� ������
	Name = TEXT("Move-21");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(-2, 1);
	this->RegisterMove(Move);
	//��� �� ��� ������ ���� � ���� �����
	Name = TEXT("Move-2-1");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(-2, -1);
	this->RegisterMove(Move);
	//��� �� ���� ������ ���� � ��� �����
	Name = TEXT("Move-1-2");
	Move = this->CreateDefaultSubobject<UMoveKnight>(Name);
	Move->SetOffset(-1, -2);
	this->RegisterMove(Move);
}