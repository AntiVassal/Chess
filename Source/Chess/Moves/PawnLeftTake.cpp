// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnLeftTake.h"
#include "../Figures/PawnFigure.h"
#include "../Board.h"
bool UPawnLeftTake::IsValidMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::IsValidMoving()) {
		return false;
	}
	APawnFigure* Pawn = Cast<APawnFigure>(this->GetDestroyFigure());
	if (Pawn == nullptr) {
		return false;
	}
	AFigure* CurrentFigure = this->GetFigure();
	EColorFigure PawnColor = Pawn->GetColor();
	if (PawnColor == CurrentFigure->GetColor()) {
		return false;
	}
	//Пешка может взять другую пешку, если ступит на клетку,
	//которую вторая пешка перепрыгнула при ходьбе на две клетки вперёд
	FFigureInfo Info = CurrentFigure->GetBoard()->GetFigureInfo(Pawn);
	return Info.CountMoves == 1 && ((Info.Row == 3 && PawnColor == EColorFigure::WHITE) ||
		(Info.Row == 4 && PawnColor == EColorFigure::BLACK));
}
FFigureInfo UPawnLeftTake::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column -= 1;
	Info.Row += this->GetFigure()->GetColor() == EColorFigure::WHITE ? 1 : -1;
	++Info.CountMoves;
	return Info;
}
AFigure* UPawnLeftTake::GetDestroyFigure() const {
	FFigureInfo BeforeInfo = this->GetFigureInfoBeforeMoving();
	FFigureInfo AfterInfo = this->GetFigureInfoAfterMoving();
	return this->GetFigure()->GetBoard()->GetFigure(BeforeInfo.Row, AfterInfo.Column);
}