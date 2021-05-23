// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnLeftDiagonal.h"
#include "../Figures/Figure.h"
bool UPawnLeftDiagonal::IsValidMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::IsValidMoving()) {
		return false;
	}
	//По диагонали пешка может только бить
	return this->GetDestroyFigure() != nullptr && this->GetDestroyFigure()->GetColor() != this->GetFigure()->GetColor();
}
FFigureInfo UPawnLeftDiagonal::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column -= 1;
	Info.Row += this->GetFigure()->GetColor() == EColorFigure::WHITE ? 1 : -1;
	++Info.CountMoves;
	return Info;
}