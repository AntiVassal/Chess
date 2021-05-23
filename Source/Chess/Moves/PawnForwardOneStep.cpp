// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnForwardOneStep.h"
#include "../Figures/Figure.h"
bool UPawnForwardOneStep::IsValidMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::IsValidMoving()) {
		return false;
	}
	//Пешка может ступить вперёд только если клетка перед ней пустая
	return this->GetDestroyFigure() == nullptr;
}
FFigureInfo UPawnForwardOneStep::GetFigureInfoAfterMoving() const {
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Row += this->GetFigure()->GetColor() == EColorFigure::WHITE ? 1 : -1;
	++Info.CountMoves;
	return Info;
}