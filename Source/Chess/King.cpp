// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "Board.h"

TArray<FMove> AKing::getMoves() const {
	TArray<FMove> res;
	FMove move;
	FColumnBoard column;
	move.fromColumn = this->getPositionColumn();
	move.fromRow = this->getPositionRow();
	if (move.fromRow > 0) {
		if (move.fromColumn > 0) {
			move.toColumn = move.fromColumn - 1;
			move.toRow = move.fromRow - 1;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
		move.toColumn = move.fromColumn;
		move.toRow = move.fromRow - 1;
		if (this->isValid(move.toRow, move.toColumn)) {
			res.Add(move);
		}
		if (move.fromColumn < 7) {
			move.toColumn = move.fromColumn + 1;
			move.toRow = move.fromRow - 1;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
	}
	if (move.fromColumn > 0) {
		move.toColumn = move.fromColumn - 1;
		move.toRow = move.fromRow;
		if (this->isValid(move.toRow, move.toColumn)) {
			res.Add(move);
		}
	}
	if (move.fromColumn < 7) {
		move.toColumn = move.fromColumn + 1;
		move.toRow = move.fromRow;
		if (this->isValid(move.toRow, move.toColumn)) {
			res.Add(move);
		}
	}
	if (move.fromRow < 7) {
		if (move.fromColumn > 0) {
			move.toColumn = move.fromColumn - 1;
			move.toRow = move.fromRow + 1;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
		move.toColumn = move.fromColumn;
		move.toRow = move.fromRow + 1;
		if (this->isValid(move.toRow, move.toColumn)) {
			res.Add(move);
		}
		if (move.fromColumn < 7) {
			move.toColumn = move.fromColumn + 1;
			move.toRow = move.fromRow + 1;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
	}
	return res;
}
bool AKing::isValid(int32 row, int32 column) const {
	auto lboard = this->getBoard();
	auto lfigure = lboard->getFigure(row, column);
	bool isValid = lfigure == nullptr || lfigure->direction != this->direction;
	if (!isValid) {
		return false;
	}
	if (row > 0) {
		if (column > 0 && this->isNotValidColumn(row - 1, column - 1)) {
			return false;
		}
		if (this->isNotValidColumn(row - 1, column)) {
			return false;
		}
		if (column < 7 && this->isNotValidColumn(row - 1, column + 1)) {
			return false;
		}
	}
	if (column > 0 && this->isNotValidColumn(row, column - 1)) {
		return false;
	}
	if (column < 7 && this->isNotValidColumn(row, column + 1)) {
		return false;
	}
	if (row < 7) {
		if (column > 0 && this->isNotValidColumn(row + 1, column - 1)) {
			return false;
		}
		if (this->isNotValidColumn(row + 1, column)) {
			return false;
		}
		if (column < 7 && this->isNotValidColumn(row + 1, column + 1)) {
			return false;
		}
	}
	return true;
}
bool AKing::isNotValidColumn(int32 row, int32 column) const {
	auto lfigure = this->getBoard()->getFigure(row, column);
	return lfigure != nullptr && lfigure->direction != this->direction && Cast<AKing>(lfigure) != nullptr;
}