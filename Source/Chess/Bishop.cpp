// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "Board.h"
bool ABishop::isValid(int32 row, int32 column, bool& canBrake)const {
	ABoard* lboard = this->getBoard();
	auto lfigure = lboard->getFigure(row, column);
	canBrake = lfigure != nullptr;
	return lfigure == nullptr || (canBrake && lfigure->direction != this->direction);
}
TArray<FMove> ABishop::getMoves() const {
	TArray<FMove> res;
	FMove move;
	move.fromColumn = this->getPositionColumn();
	move.fromRow = this->getPositionRow();
	for (int32 i = 1; i < 8; ++i) {
		move.toColumn = move.fromColumn - i;
		move.toRow = move.fromRow - i;
		if (move.toColumn < 0 || move.toRow < 0) {
			break;
		}
		bool isBreak = false;
		if (this->isValid(move.toRow, move.toColumn, isBreak)) {
			res.Add(move);
		}
		if (isBreak) {
			break;
		}
	}
	for (int32 i = 1; i < 8; ++i) {
		move.toColumn = move.fromColumn + i;
		move.toRow = move.fromRow - i;
		if (move.toColumn > 7 || move.toRow < 0) {
			break;
		}
		bool isBreak = false;
		if (this->isValid(move.toRow, move.toColumn, isBreak)) {
			res.Add(move);
		}
		if (isBreak) {
			break;
		}
	}
	for (int32 i = 1; i < 8; ++i) {
		move.toColumn = move.fromColumn - i;
		move.toRow = move.fromRow + i;
		if (move.toColumn < 0 || move.toRow > 7) {
			break;
		}
		bool isBreak = false;
		if (this->isValid(move.toRow, move.toColumn, isBreak)) {
			res.Add(move);
		}
		if (isBreak) {
			break;
		}
	}
	for (int32 i = 1; i < 8; ++i) {
		move.toColumn = move.fromColumn + i;
		move.toRow = move.fromRow + i;
		if (move.toColumn > 7 || move.toRow > 7) {
			break;
		}
		bool isBreak = false;
		if (this->isValid(move.toRow, move.toColumn, isBreak)) {
			res.Add(move);
		}
		if (isBreak) {
			break;
		}
	}
	return res;
}