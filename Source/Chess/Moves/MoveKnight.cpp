// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKnight.h"
#include "../Figures/Figure.h"
bool UMoveKnight::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	//��� �������� ������ ���� ������ ���������� �����, ��� ��� ��������� ������, ������� ����� ������
	AFigure* DestroyFigure = this->GetDestroyFigure();
	return DestroyFigure == nullptr || DestroyFigure->GetColor() != this->GetFigure()->GetColor();
}
FFigureInfo UMoveKnight::GetFigureInfoAfterMoving() const {
	FFigureInfo info = this->GetFigureInfoBeforeMoving();
	info.Column += this->OffsetColumn;
	info.Row += this->OffsetRow;
	++info.CountMoves;
	return info;
}
void UMoveKnight::SetOffset(int8 Row, int8 Column) {
	this->OffsetRow = Row;
	this->OffsetColumn = Column;
}