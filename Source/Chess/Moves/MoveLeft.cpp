// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLeft.h"
#include "../Figures/Figure.h"
#include "../Board.h"
void UMoveLeft::SetLength(int8 Length) {
	this->LengthMove = Length;
}
bool UMoveLeft::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	for (int8 i = 1; i < this->LengthMove; ++i) {
		AFigure* DestFigure = Board->GetFigure(Info.Row, Info.Column - i);
		if (DestFigure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	AFigure* DestroyFigure = this->GetDestroyFigure();
	return DestroyFigure == nullptr || DestroyFigure->GetColor() != CurrentFigure->GetColor();
}
FFigureInfo UMoveLeft::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column -= this->LengthMove;
	++Info.CountMoves;
	return Info;
}