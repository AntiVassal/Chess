// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "Board.h"
bool AKnight::isValid(int32 row, int32 column) const {
	auto lboard = this->getBoard();
	auto lfigure = lboard->getFigure(row, column );
	return lfigure == nullptr || lfigure->direction != this->direction;
}
TArray<FMove> AKnight::getMoves() const {
	TArray<FMove> res;
	FMove move;
	move.fromColumn = this->getPositionColumn();
	move.fromRow = this->getPositionRow();
	if (move.fromRow > 0) {
		if (move.fromColumn > 1) {
			move.toRow = move.fromRow - 1;
			move.toColumn = move.fromColumn - 2;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
		if (move.fromColumn < 6) {
			move.toRow = move.fromRow - 1;
			move.toColumn = move.fromColumn + 2;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
		if (move.fromRow > 1) {
			if (move.fromColumn > 0) {
				move.toRow = move.fromRow - 2;
				move.toColumn = move.fromColumn - 1;
				if (this->isValid(move.toRow, move.toColumn)) {
					res.Add(move);
				}
			}
			if (move.fromColumn < 7) {
				move.toRow = move.fromRow - 2;
				move.toColumn = move.fromColumn + 1;
				if (this->isValid(move.toRow, move.toColumn)) {
					res.Add(move);
				}
			}
		}
	}
	if (move.fromRow < 7) {
		if (move.fromColumn > 1) {
			move.toRow = move.fromRow + 1;
			move.toColumn = move.fromColumn - 2;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
		if (move.fromColumn < 6) {
			move.toRow = move.fromRow + 1;
			move.toColumn = move.fromColumn + 2;
			if (this->isValid(move.toRow, move.toColumn)) {
				res.Add(move);
			}
		}
		if (move.fromRow < 6) {
			if (move.fromColumn > 0) {
				move.toRow = move.fromRow + 2;
				move.toColumn = move.fromColumn - 1;
				if (this->isValid(move.toRow, move.toColumn)) {
					res.Add(move);
				}
			}
			if (move.fromColumn < 7) {
				move.toRow = move.fromRow + 2;
				move.toColumn = move.fromColumn + 1;
				if (this->isValid(move.toRow, move.toColumn)) {
					res.Add(move);
				}
			}
		}
	}
	return res;
}