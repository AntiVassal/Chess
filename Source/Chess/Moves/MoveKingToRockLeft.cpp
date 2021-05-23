// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKingToRockLeft.h"
#include "../Figures/Figure.h"
#include "../Board.h"
bool UMoveKingToRockLeft::IsValidMoving() {
	//���������, �� ������� �� ��� � ���� � �� ������ �� �� �� ������� �����
	if (!Super::IsValidMoving()) {
		return false;
	}
	//��������� �������� ������ ���� ������ �� ���� �� �����
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	if (Info.CountMoves > 0) {
		return false;
	}
	AFigure* CurrentFigure = this->GetFigure();
	ABoard* Board = CurrentFigure->GetBoard();
	//��������� �������� ������ ���� ����� �� ���� �� ������
	AFigure* RockFigure = Board->GetFigure(Info.Row, 0);
	if (RockFigure == nullptr) {
		return false;
	}
	FFigureInfo RockInfo = Board->GetFigureInfo(RockFigure);
	if (RockInfo.CountMoves > 0) {
		return false;
	}
	//��������� �������� ������ ���� ����� ������ � ������ ��� ������ �����
	for (int8 i = 1; i < Info.Column; ++i) {
		AFigure* Figure = this->GetFigure()->GetBoard()->GetFigure(Info.Row, i);
		if (Figure != nullptr) {
			return false;
		}
	}
	return true;
}
void UMoveKingToRockLeft::Move() {
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	//���� ���, ������� ���������� ����� �� ������ ����� �� ������, � ��������� ���
	AFigure* RockFigure = this->GetFigure()->GetBoard()->GetFigure(Info.Row, 0);
	TArray<UMoveFigure*> Moves;
	RockFigure->GetMoves(Moves);
	for (auto Move : Moves) {
		auto RockFigureMoveInfo = Move->GetFigureInfoAfterMoving();
		if (RockFigureMoveInfo.Row == Info.Row && RockFigureMoveInfo.Column == Info.Column - 1) {
			Move->Move();
			break;
		}
	}
	//������ ����������� ������ ��� ���������� � ������� ������.
	Super::Move();
}
void UMoveKingToRockLeft::Rollback() {
	//��������� ��� ���������� ����, �� ������� ���������� ����, � ����� - ������,
	//�� ��� ������ �����, ����� ��������� �� ��� ���� �����
	Super::Rollback();
	Super::Rollback();
}
FFigureInfo UMoveKingToRockLeft::GetFigureInfoAfterMoving() const{
	FFigureInfo Info = this->GetFigureInfoBeforeMoving();
	Info.Column -= 2;
	++Info.CountMoves;
	return Info;
}
void UMoveKingToRockLeft::FinishMove() {
	//��������� � ���������� ���� ����� ���������������,
	//��������� ��� ���������� ���� �������� ��������� ����� � ���������� ����������� �����
}