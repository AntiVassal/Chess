// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKnight.h"
#include "../Figures/Figure.h"
bool UMoveKnight::IsValidMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::IsValidMoving()) {
		return false;
	}
	//Ход возможен только если клетка назначения пуста, или там находится фигура, которую можно съесть
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