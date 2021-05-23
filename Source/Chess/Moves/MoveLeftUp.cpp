// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLeftUp.h"
#include "../Figures/Figure.h"
#include "../Board.h"
void UMoveLeftUp::SetLength(int8 Length) {
	this->LengthMove = Length;
}
bool UMoveLeftUp::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	//���� ����� ������� � ������� ���������� ���� ������ ������, �� ��� ����������
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	for (int8 i = 1; i < this->LengthMove; ++i) {
		AFigure* Figure = Board->GetFigure(Info.Row + i, Info.Column - i);
		if (Figure != nullptr) {
			return false;
		}
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	AFigure* DestroyFigure = this->GetDestroyFigure();
	return DestroyFigure == nullptr || DestroyFigure->GetColor() != CurrentFigure->GetColor();
}
FFigureInfo UMoveLeftUp::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column -= this->LengthMove;
	Info.Row += this->LengthMove;
	++Info.CountMoves;
	return Info;
}

