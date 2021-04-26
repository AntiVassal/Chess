// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChessPawn.h"
#include "Board.h"
#include "Figure.h"
#include "MoveFigure.h"
void AAIChessPawn::whaitMove_Implementation() {
	TArray<UMoveFigure*> moves;
	//��������� ������ �����
	this->minimax(4, this->direction, &moves);
	if (moves.Num() > 0) {
		//����� ���������� ����
		moves[FMath::RandRange(0, moves.Num() - 1)]->move();
	}else{
		//���� ��� �����, �� ��������
		this->board->lose(this);
	}
}
float AAIChessPawn::minimax(int32 depth, DirectionFigure figureDirection, TArray<UMoveFigure*>* move) {
	if (depth == 0) {
		//���� ������� ����, �� ��������� ��� ���� ����� �� �����
		return this->board->getPower(DirectionFigure::WHITE) - this->board->getPower(DirectionFigure::BLACK);
	}
	TArray<UMoveFigure*> moves;
	//�������� ��� ��������� ����
	this->board->getAllMoves(moves, figureDirection);
	//��� ������ ���������, ����� ������������ ������ ��������� �����. ���� ��������� �� ���� ��������, �������� �.
	bool isSimulated = this->board->isSimulated();
	if (!isSimulated) {
		this->board->startSimulation();
	}
	switch (figureDirection)
	{
	case WHITE: {
		float bestMove = -9999;
		for (auto lmove : moves) {
			//��������� ����
			lmove->move();
			//��������������� ������� ����
			auto power = this->board->getPower(DirectionFigure::WHITE) - this->board->getPower(DirectionFigure::BLACK);
			if (FMath::IsNearlyEqual(bestMove, power) || power > bestMove) {
				//���� ��������������� ������� ���� ������� �������� ���, �� ������������� ��������� ���� ����������
				power = this->minimax(depth - 1, DirectionFigure::BLACK, nullptr);
				//���� ����� ��������� ����� ���������� ��� �� ��� ���������� ������, �� ��������� ���� ���.
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
			//���������� ��������� �����
			lmove->rollback();
		}
		//������������� ���������
		if (!isSimulated) {
			this->board->stopSimulation();
		}
		return bestMove;

	}
	case BLACK: {
		float bestMove = 9999;
		for (auto lmove : moves) {
			//��������� ����
			lmove->move();
			//��������������� ������� ����
			auto power = this->board->getPower(DirectionFigure::WHITE) - this->board->getPower(DirectionFigure::BLACK);
			if (FMath::IsNearlyEqual(bestMove, power) || power < bestMove) {
				//���� ��������������� ������� ���� ������� �������� ���, �� ������������� ��������� ���� ����������
				power = this->minimax(depth - 1, DirectionFigure::WHITE, nullptr);
				//���� ����� ��������� ����� ���������� ��� �� ��� ���������� ������, �� ��������� ���� ���.
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
			//���������� ��������� �����
			lmove->rollback();
		}
		//������������� ���������
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
	//����� ����� ������� �� �����, �������� � �� �����
	this->board->setFigure(this->direction == DirectionFigure::WHITE ? this->board->queenWhite : this->board->queenBlack,
		row, column, this->direction);
}
//��� �� �� ����� ���������� ��������� � �������� ��� ���������
void AAIChessPawn::win_Implementation(){}
void AAIChessPawn::lose_Implementation() {}