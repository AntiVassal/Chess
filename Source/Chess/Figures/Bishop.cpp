// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "../Board.h"
#include "../Moves/MoveLeftUp.h"
#include "../Moves/MoveRightUp.h"
#include "../Moves/MoveRightDown.h"
#include "../Moves/MoveLeftDown.h"
float ABishop::GetPower(int8 Row, int8 Column) const {
	//���� ������ ������, �� ������������� �������.
	if (this->GetColor() == EColorFigure::BLACK) {
		Row = 7 - Row;
	}
	return 30.0f + PowerMatrix[Row][Column];
}
ABishop::ABishop() {
	//���������� ���������� ������
	for (int8 i = 1; i < 8; ++i) {
		FString Name = TEXT("MoveLeftUp");
		Name.AppendInt(i);
		//��� ����� � ���� �� ��������� �� i ������
		UMoveLeftUp* LeftUp = this->CreateDefaultSubobject<UMoveLeftUp>(FName(Name));
		LeftUp->SetLength(i);
		this->RegisterMove(LeftUp);
		Name = TEXT("MoveRightUp");
		Name.AppendInt(i);
		//��� ������ � ���� �� ��������� �� i ������
		UMoveRightUp* RightUp = this->CreateDefaultSubobject<UMoveRightUp>(FName(Name));
		RightUp->SetLength(i);
		this->RegisterMove(RightUp);
		Name = TEXT("MoveRightDown");
		Name.AppendInt(i);
		//��� ������ � ��� �� ��������� �� i ������
		UMoveRightDown* RightDown = this->CreateDefaultSubobject<UMoveRightDown>(FName(Name));
		RightDown->SetLength(i);
		this->RegisterMove(RightDown);
		Name = TEXT("MoveLeftDown");
		Name.AppendInt(i);
		//��� ����� � ��� �� ��������� �� i ������
		UMoveLeftDown* LeftDown = this->CreateDefaultSubobject<UMoveLeftDown>(FName(Name));
		LeftDown->SetLength(i);
		this->RegisterMove(LeftDown);
	}
}