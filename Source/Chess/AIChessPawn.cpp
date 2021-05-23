// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChessPawn.h"
#include "Board.h"
#include "Figures/Figure.h"
#include "Moves/MoveFigure.h"
void AAIChessPawn::WhaitNextMove_Implementation() {
	TArray<UMoveFigure*> Moves;
	//��������� ������ �����
	this->Minimax(4, this->ColorSide, &Moves);
	if (Moves.Num() > 0) {
		//����� ���������� ����
		Moves[FMath::RandRange(0, Moves.Num() - 1)]->Move();
	}else{
		//���� ��� �����, �� ������� ���������
		this->BoardActor->Lose(this);
	}
}
float AAIChessPawn::Minimax(int32 Depth, EColorFigure FigureDirection, TArray<UMoveFigure*>* Move) {
	if (Depth == 0) {
		//���� ������� ����, �� ��������� ��� ���� ����� �� �����
		return this->BoardActor->GetPowerAllFigures(EColorFigure::WHITE) -
			this->BoardActor->GetPowerAllFigures(EColorFigure::BLACK);
	}
	TArray<UMoveFigure*> Moves;
	//�������� ��� ��������� ����
	this->BoardActor->GetAllMoves(Moves, FigureDirection);
	//��� ������ ���������, ����� ������������ ������ ��������� �����. ���� ��������� �� ���� ��������, �������� �.
	bool IsSimulated = this->BoardActor->IsSimulated();
	if (!IsSimulated) {
		this->BoardActor->StartSimulation();
	}
	switch (FigureDirection)
	{
	case EColorFigure::WHITE: {
		float BestMove = -9999;
		for (UMoveFigure* LMove : Moves) {
			//��������� ����
			LMove->Move();
			//��������������� ������� ����
			float Power = this->BoardActor->GetPowerAllFigures(EColorFigure::WHITE) -
				this->BoardActor->GetPowerAllFigures(EColorFigure::BLACK);
			if (FMath::IsNearlyEqual(BestMove, Power) || Power > BestMove) {
				//���� ��������������� ������� ���� ������� �������� ���, �� ������������� ��������� ���� ����������
				Power = this->Minimax(Depth - 1, EColorFigure::BLACK, nullptr);
				//���� ����� ��������� ����� ���������� ��� �� ��� ���������� ������, �� ��������� ���� ���.
				if (Power > BestMove || FMath::IsNearlyEqual(Power, BestMove)) {
					BestMove = Power;
					if (Move != nullptr) {
						//���� ��� ���� ������, ��� � ���������� �����, �� ������� ������ �� ���
						if (!FMath::IsNearlyEqual(Power, BestMove)) {
							Move->Empty();
						}
						Move->Add(LMove);
					}
				}
			}
			//���������� ��������� �����
			LMove->Rollback();
		}
		//������������� ���������
		if (!IsSimulated) {
			this->BoardActor->StopSimulation();
		}
		return BestMove;

	}
	case EColorFigure::BLACK: {
		float BestMove = 9999;
		for (UMoveFigure* LMove : Moves) {
			//��������� ����
			LMove->Move();
			//��������������� ������� ����
			float Power = this->BoardActor->GetPowerAllFigures(EColorFigure::WHITE) -
				this->BoardActor->GetPowerAllFigures(EColorFigure::BLACK);
			if (FMath::IsNearlyEqual(BestMove, Power) || Power < BestMove) {
				//���� ��������������� ������� ���� ������� �������� ���, �� ������������� ��������� ���� ����������
				Power = this->Minimax(Depth - 1, EColorFigure::WHITE, nullptr);
				//���� ����� ��������� ����� ���������� ��� �� ��� ���������� ������, �� ��������� ���� ���.
				if (Power < BestMove || FMath::IsNearlyEqual(Power, BestMove)) {
					BestMove = Power;
					if (Move != nullptr) {
						//���� ��� ���� ������, ��� � ���������� �����, �� ������� ������ �� ���
						if (!FMath::IsNearlyEqual(Power, BestMove)) {
							Move->Empty();
						}
						Move->Add(LMove);
					}
				}
			}
			//���������� ��������� �����
			LMove->Rollback();
		}
		//������������� ���������
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
	//����� ����� ������� �� �����, �������� � �� �����
	this->BoardActor->SetFigure(this->ColorSide == EColorFigure::WHITE ?
		this->BoardActor->QueenWhite : this->BoardActor->QueenBlack,
		row, column, this->ColorSide);
}
//��� �� �� ����� ���������� ��������� � �������� ��� ���������
void AAIChessPawn::Win_Implementation(){}
void AAIChessPawn::Lose_Implementation() {}