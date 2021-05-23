// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForwardTwoSteps.h"
#include "../Figures/Figure.h"
#include "../Board.h"
bool UPawnForwardTwoSteps::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* CurrentFigure = this->GetFigure();
	//����� ����� ������� ����� ������ ���� ��� ������ � ��� � ��� ������ ����� ��� ������
	if (CurrentFigure->GetBoard()->GetFigure(
		Info.Row + (CurrentFigure->GetColor() == EColorFigure::WHITE ? 1 : -1),
		Info.Column) != nullptr) {
		return false;
	}
	return this->GetDestroyFigure() == nullptr && Info.CountMoves == 0;
}
FFigureInfo UPawnForwardTwoSteps::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Row += this->GetFigure()->GetColor() == EColorFigure::WHITE ? 2 : -2;
	++Info.CountMoves;
	return Info;
}