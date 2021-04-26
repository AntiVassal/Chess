// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChessPawn.h"
#include "Board.h"
#include "Figure.h"
#include "MoveFigure.h"
void AAIChessPawn::whaitMove_Implementation() {
	TArray<UMoveFigure*> moves;
	//Получение лучших ходов
	this->minimax(4, this->direction, &moves);
	if (moves.Num() > 0) {
		//Выбор случайного хода
		moves[FMath::RandRange(0, moves.Num() - 1)]->move();
	}else{
		//Если нет ходов, то проиграл
		this->board->lose(this);
	}
}
float AAIChessPawn::minimax(int32 depth, DirectionFigure figureDirection, TArray<UMoveFigure*>* move) {
	if (depth == 0) {
		//Если глубина ноль, то посчитать вес всех фигур на доске
		return this->board->getPower(DirectionFigure::WHITE) - this->board->getPower(DirectionFigure::BLACK);
	}
	TArray<UMoveFigure*> moves;
	//Получаем все доступные ходы
	this->board->getAllMoves(moves, figureDirection);
	//Для работы алгоритма, нужно симулировать разные состояния доски. Если симуляция не была включена, включаем её.
	bool isSimulated = this->board->isSimulated();
	if (!isSimulated) {
		this->board->startSimulation();
	}
	switch (figureDirection)
	{
	case WHITE: {
		float bestMove = -9999;
		for (auto lmove : moves) {
			//Симуляция хода
			lmove->move();
			//Предварительный подсчёт веса
			auto power = this->board->getPower(DirectionFigure::WHITE) - this->board->getPower(DirectionFigure::BLACK);
			if (FMath::IsNearlyEqual(bestMove, power) || power > bestMove) {
				//Если предварительный подсчёт веса показал выгодный ход, то предсказываем возможные ходы противника
				power = this->minimax(depth - 1, DirectionFigure::BLACK, nullptr);
				//Если после возможных ходов противника вес всё ещё показывает выгоду, то сохраняем этот ход.
				if (power > bestMove || FMath::IsNearlyEqual(power, bestMove)) {
					bestMove = power;
					if (move != nullptr) {
						if (!FMath::IsNearlyEqual(power, bestMove)) {
							move->Empty();
						}
						move->Add(lmove);
					}
				}
			}
			//Откатываем состояние доски
			lmove->rollback();
		}
		//Останавливаем симуляцию
		if (!isSimulated) {
			this->board->stopSimulation();
		}
		return bestMove;

	}
	case BLACK: {
		float bestMove = 9999;
		for (auto lmove : moves) {
			//Симуляция хода
			lmove->move();
			//Предварительный подсчёт веса
			auto power = this->board->getPower(DirectionFigure::WHITE) - this->board->getPower(DirectionFigure::BLACK);
			if (FMath::IsNearlyEqual(bestMove, power) || power < bestMove) {
				//Если предварительный подсчёт веса показал выгодный ход, то предсказываем возможные ходы противника
				power = this->minimax(depth - 1, DirectionFigure::WHITE, nullptr);
				//Если после возможных ходов противника вес всё ещё показывает выгоду, то сохраняем этот ход.
				if (power < bestMove || FMath::IsNearlyEqual(power, bestMove)) {
					bestMove = power;
					if (move != nullptr) {
						if (!FMath::IsNearlyEqual(power, bestMove)) {
							move->Empty();
						}
						move->Add(lmove);
					}
				}
			}
			//Откатываем состояние доски
			lmove->rollback();
		}
		//Останавливаем симуляцию
		if (!isSimulated) {
			this->board->stopSimulation();
		}
		return bestMove;

	}
	}
	if (!isSimulated) {
		this->board->stopSimulation();
	}
	return 0.0f;
}
void AAIChessPawn::pawnEndPath_Implementation(int32 row, int32 column) {
	//Когда пешка доходит до конца, заменяем её на ферзя
	this->board->setFigure(this->direction == DirectionFigure::WHITE ? this->board->queenWhite : this->board->queenBlack,
		row, column, this->direction);
}
//Для ИИ не нужно отображать сообщений о выиграше или проиграше
void AAIChessPawn::win_Implementation(){}
void AAIChessPawn::lose_Implementation() {}