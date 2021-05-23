// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveFigure.h"
#include "../Figures/King.h"
#include "../Board.h"

bool UMoveFigure::IsValidMoving() {
	//Проверка на выход за пределы доски
	FFigureInfo Info = this->GetFigureInfoAfterMoving();
	if (Info.Column < 0 || Info.Column >= 8 || Info.Row < 0 || Info.Row >= 8) {
		return false;
	}
	//Проверяем не приведёт ли текущий ход к мату
	bool IsMove = true;
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	if (!Board->IsSimulated()) {
		//Включаем симуляцию
		Board->StartSimulation();
		if (this->IsValidMoving()) {
			//Если ход возможен, то выполняем его
			this->Move();
			//Проверяем не привёл ли ход к шаху
			IsMove =!Board->GetKing(CurrentFigure->GetColor())->IsCheck();
			//Откатываем состояние доски
			this->Rollback();
		}
		//Останавливаем симуляцию
		Board->StopSimulation();
		return IsMove;
	}
	return IsMove;
}
AFigure* UMoveFigure::GetDestroyFigure() const {
	FFigureInfo Info = this->GetFigureInfoAfterMoving();
	return this->GetFigure()->GetBoard()->GetFigure(Info.Row, Info.Column);
}
void UMoveFigure::Move(){
	this->GetFigure()->GetBoard()->MoveFigureOnBoard(this);
}
void UMoveFigure::Rollback() {
	this->GetFigure()->GetBoard()->RollbackBoard();
}
FFigureInfo UMoveFigure::GetFigureInfoAfterMoving() const{
	return FFigureInfo();
}
FFigureInfo UMoveFigure::GetFigureInfoBeforeMoving() const{
	AFigure* Figure = this->GetFigure();
	return Figure->GetBoard()->GetFigureInfo(Figure);
}
AFigure* UMoveFigure::GetFigure() const {
	return this->FigureActor;
}
void UMoveFigure::Initialzie(class AFigure* Figure) {
	this->FigureActor = Figure;
}
void UMoveFigure::FinishMove() {
	this->GetFigure()->GetBoard()->TogleNextMove();
}