// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveKingToRockRight.h"
#include "../Figures/Figure.h"
#include "../Board.h"
bool UMoveKingToRockRight::IsValidMoving() {
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
	AFigure* RockFigure = Board->GetFigure(Info.Row, 7);
	if (RockFigure == nullptr) {
		return false;
	}
	FFigureInfo RockFigureInfo = Board->GetFigureInfo(RockFigure);
	if (RockFigureInfo.CountMoves > 0) {
		return false;
	}
	//��������� �������� ������ ���� ����� ������ � ������ ��� ������ �����
	for (int8 i = Info.Column + 1; i < 7; ++i) {
		AFigure* Figure = this->GetFigure()->GetBoard()->GetFigure(Info.Row, i);
		if (Figure != nullptr) {
			return false;
		}
	}
	return true;
}
void UMoveKingToRockRight::Move() {
	//���� ���, ������� ���������� ����� �� ������ ����� �� ������, � ��������� ���
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
	//������ ����������� ������ ��� ���������� � ������� ������.
	Super::Move();
}
void UMoveKingToRockRight::Rollback() {
	//��������� ��� ���������� ����, �� ������� ���������� ����, � ����� - ������,
	//�� ��� ������ �����, ����� ��������� �� ��� ���� �����
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
	//��������� � ���������� ���� ����� ���������������,
	//��������� ��� ���������� ���� �������� ��������� ����� � ���������� ����������� �����
}