// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveUp.h"
#include "../Figures/Figure.h"
#include "../Board.h"
void UMoveUp::SetLength(int8 Length) {
	this->LengthMove = Length;
}
bool UMoveUp::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	for (int8 i = 1; i < this->LengthMove; ++i) {
		AFigure* DestFigure = Board->GetFigure(Info.Row + i, Info.Column);
		if (DestFigure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	AFigure* DestroyFigure = this->GetDestroyFigure();
	return DestroyFigure == nullptr || DestroyFigure->GetColor() != CurrentFigure->GetColor();
}
FFigureInfo UMoveUp::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Row += this->LengthMove;
	++Info.CountMoves;
	return Info;
}