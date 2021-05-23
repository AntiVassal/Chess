// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveRight.h"
#include "../Figures/Figure.h"
#include "../Board.h"
void UMoveRight::SetLength(int8 Length) {
	this->LengthMove = Length;
}
bool UMoveRight::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	for (int8 i = 1; i < this->LengthMove; ++i) {
		AFigure* DestFigure = Board->GetFigure(Info.Row, Info.Column + i);
		if (DestFigure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	AFigure* DestFigure = this->GetDestroyFigure();
	return DestFigure == nullptr || DestFigure->GetColor() != CurrentFigure->GetColor();
}
FFigureInfo UMoveRight::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column += this->LengthMove;
	++Info.CountMoves;
	return Info;
}