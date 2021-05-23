// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveDown.h"
#include "../Figures/Figure.h"
#include "../Board.h"
void UMoveDown::SetLength(int8 Length) {
	this->LengthMove = Length;
}
bool UMoveDown::IsValidMoving() {
	//ѕровер€ем, не приведЄт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::IsValidMoving()) {
		return false;
	}
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	//≈сли между фигурой и клеткой назначени€ есть другие фигуры, то ход невозможен
	for (int8 i = 1; i < this->LengthMove; ++i) {
		AFigure* DestFigure = Board->GetFigure(Info.Row - i, Info.Column);
		if (DestFigure != nullptr) {
			return false;
		}
	}
	//’од возможен только если клетка назначени€ пуста, или там находитс€ фигура, которую можно съесть
	AFigure* DestFigure = this->GetDestroyFigure();
	return DestFigure == nullptr || DestFigure->GetColor() != CurrentFigure->GetColor();
}
FFigureInfo UMoveDown::GetFigureInfoAfterMoving() const {
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Row -= this->LengthMove;
	++Info.CountMoves;
	return Info;
}