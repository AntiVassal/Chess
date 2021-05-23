// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForwardOneStep.h"
#include "../Figures/Figure.h"
bool UPawnForwardOneStep::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	//����� ����� ������� ����� ������ ���� ������ ����� ��� ������
	return this->GetDestroyFigure() == nullptr;
}
FFigureInfo UPawnForwardOneStep::GetFigureInfoAfterMoving() const {
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Row += this->GetFigure()->GetColor() == EColorFigure::WHITE ? 1 : -1;
	++Info.CountMoves;
	return Info;
}