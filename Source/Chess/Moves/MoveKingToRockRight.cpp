// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKingToRockRight.h"
#include "../Figures/Figure.h"
#include "../Board.h"
bool UMoveKingToRockRight::IsValidMoving() {
	//Проверяем, не приведёт ли ход к мату и не выйдет ли он за пределы доски
	if (!Super::IsValidMoving()) {
		return false;
	}
	//Рокировка возможна только если король не разу не ходил
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	if (Info.CountMoves > 0) {
		return false;
	}
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	//Рокировка возможна только если башня не разу не ходила
	AFigure* RockFigure = Board->GetFigure(Info.Row, 7);
	if (RockFigure == nullptr) {
		return false;
	}
	FFigureInfo RockFigureInfo = Board->GetFigureInfo(RockFigure);
	if (RockFigureInfo.CountMoves > 0) {
		return false;
	}
	//Рокировка возможна только если между королём и башней нет других фигур
	for (int8 i = Info.Column + 1; i < 7; ++i) {
		AFigure* Figure = this->GetFigure()->GetBoard()->GetFigure(Info.Row, i);
		if (Figure != nullptr) {
			return false;
		}
	}
	return true;
}
void UMoveKingToRockRight::Move() {
	//Ищем ход, который переместит башню на клетку слева от короля, и выполняем его
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	AFigure* RockFigure = this->GetFigure()->GetBoard()->GetFigure(Info.Row, 7);
	TArray<UMoveFigure*> Moves;
	RockFigure->GetMoves(Moves);
	for (UMoveFigure* Move : Moves) {
		FFigureInfo RockFigureMoveInfo = Move->GetFigureInfoAfterMoving();
		if (RockFigureMoveInfo.Row == Info.Row && RockFigureMoveInfo.Column == Info.Column + 1) {
			Move->Move();
			break;
		}
	}
	//Логика перемещения фигуры уже определена в базовом классе.
	Super::Move();
}
void UMoveKingToRockRight::Rollback() {
	//Поскольку при выполнении хода, мы сначала перемещаем баню, а затем - короля,
	//то при откате доски, нужно вернуться на два шага назад
	Super::Rollback();
	Super::Rollback();
}
FFigureInfo UMoveKingToRockRight::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column += 2;
	++Info.CountMoves;
	return Info;
}
void UMoveKingToRockRight::FinishMove() {
	//Сообщение о завершении хода будет проигнорировано,
	//поскольку при выполнении хода поступит сообщение также о завершении перемещения башни
}