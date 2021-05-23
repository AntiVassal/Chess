// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChessPawn.h"
#include "Board.h"
#include "Figures/Figure.h"
#include "Moves/MoveFigure.h"
void AAIChessPawn::WhaitNextMove_Implementation() {
	TArray<UMoveFigure*> Moves;
	//Получение лучших ходов
	this->Minimax(4, this->ColorSide, &Moves);
	if (Moves.Num() > 0) {
		//Выбор случайного хода
		Moves[FMath::RandRange(0, Moves.Num() - 1)]->Move();
	}else{
		//Если нет ходов, то признаём поражение
		this->BoardActor->Lose(this);
	}
}
float AAIChessPawn::Minimax(int32 Depth, EColorFigure FigureDirection, TArray<UMoveFigure*>* Move) {
	if (Depth == 0) {
		//Если глубина ноль, то посчитать вес всех фигур на доске
		return this->BoardActor->GetPowerAllFigures(EColorFigure::WHITE) -
			this->BoardActor->GetPowerAllFigures(EColorFigure::BLACK);
	}
	TArray<UMoveFigure*> Moves;
	//Получаем все доступные ходы
	this->BoardActor->GetAllMoves(Moves, FigureDirection);
	//Для работы алгоритма, нужно симулировать разные состояния доски. Если симуляция не была включена, включаем её.
	bool IsSimulated = this->BoardActor->IsSimulated();
	if (!IsSimulated) {
		this->BoardActor->StartSimulation();
	}
	switch (FigureDirection)
	{
	case EColorFigure::WHITE: {
		float BestMove = -9999;
		for (UMoveFigure* LMove : Moves) {
			//Симуляция хода
			LMove->Move();
			//Предварительный подсчёт веса
			float Power = this->BoardActor->GetPowerAllFigures(EColorFigure::WHITE) -
				this->BoardActor->GetPowerAllFigures(EColorFigure::BLACK);
			if (FMath::IsNearlyEqual(BestMove, Power) || Power > BestMove) {
				//Если предварительный подсчёт веса показал выгодный ход, то предсказываем возможные ходы противника
				Power = this->Minimax(Depth - 1, EColorFigure::BLACK, nullptr);
				//Если после возможных ходов противника вес всё ещё показывает выгоду, то сохраняем этот ход.
				if (Power > BestMove || FMath::IsNearlyEqual(Power, BestMove)) {
					BestMove = Power;
					if (Move != nullptr) {
						//Если вес хода лучший, чем в сохранённых ходов, то очищаем массив от них
						if (!FMath::IsNearlyEqual(Power, BestMove)) {
							Move->Empty();
						}
						Move->Add(LMove);
					}
				}
			}
			//Откатываем состояние доски
			LMove->Rollback();
		}
		//Останавливаем симуляцию
		if (!IsSimulated) {
			this->BoardActor->StopSimulation();
		}
		return BestMove;

	}
	case EColorFigure::BLACK: {
		float BestMove = 9999;
		for (UMoveFigure* LMove : Moves) {
			//Симуляция хода
			LMove->Move();
			//Предварительный подсчёт веса
			float Power = this->BoardActor->GetPowerAllFigures(EColorFigure::WHITE) -
				this->BoardActor->GetPowerAllFigures(EColorFigure::BLACK);
			if (FMath::IsNearlyEqual(BestMove, Power) || Power < BestMove) {
				//Если предварительный подсчёт веса показал выгодный ход, то предсказываем возможные ходы противника
				Power = this->Minimax(Depth - 1, EColorFigure::WHITE, nullptr);
				//Если после возможных ходов противника вес всё ещё показывает выгоду, то сохраняем этот ход.
				if (Power < BestMove || FMath::IsNearlyEqual(Power, BestMove)) {
					BestMove = Power;
					if (Move != nullptr) {
						//Если вес хода лучший, чем в сохранённых ходов, то очищаем массив от них
						if (!FMath::IsNearlyEqual(Power, BestMove)) {
							Move->Empty();
						}
						Move->Add(LMove);
					}
				}
			}
			//Откатываем состояние доски
			LMove->Rollback();
		}
		//Останавливаем симуляцию
		if (!IsSimulated) {
			this->BoardActor->StopSimulation();
		}
		return BestMove;

	}
	}
	if (!IsSimulated) {
		this->BoardActor->StopSimulation();
	}
	return 0.0f;
}
void AAIChessPawn::OnPawnEndPath_Implementation(int32 row, int32 column) {
	//Когда пешка доходит до конца, заменяем её на ферзя
	this->BoardActor->SetFigure(this->ColorSide == EColorFigure::WHITE ?
		this->BoardActor->QueenWhite : this->BoardActor->QueenBlack,
		row, column, this->ColorSide);
}
//Для ИИ не нужно отображать сообщений о выиграше или проиграше
void AAIChessPawn::Win_Implementation(){}
void AAIChessPawn::Lose_Implementation() {}