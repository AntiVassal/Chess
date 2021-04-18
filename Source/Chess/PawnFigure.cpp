// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnFigure.h"
#include "Board.h"

APawnFigure::APawnFigure() {
	this->bIsFirstMove = true;
}
TArray<FMove> APawnFigure::getMoves() const {
	TArray<FMove> res;
	FMove move;
	move.fromColumn = this->getPositionColumn();
	move.fromRow = this->getPositionRow();
	if (move.fromRow == 7 && this->direction == DirectionFigure::WHITE ||
		move.fromRow == 0 && this->direction == DirectionFigure::BLACK) {
		return res;
	}
	auto lboard = this->getBoard();
	move.toColumn = move.fromColumn;
	move.toRow = this->getNextRow(move.fromRow);
	UE_LOG(LogTemp, Display, TEXT("%dx%d"), move.toRow, move.toColumn);
	auto lfigure = lboard->getFigure(move.toRow, move.toColumn);
	if (lfigure == nullptr) {
		res.Add(move);
	}
	if (move.fromColumn > 0) {
		move.toColumn = move.fromColumn - 1;
		lfigure = lboard->getFigure(move.toRow, move.toColumn);
		if (lfigure != nullptr && lfigure->direction != this->direction) {
			res.Add(move);
		}
	}
	if (move.fromColumn < 7) {
		move.toColumn = move.fromColumn + 1;
		lfigure = lboard->getFigure(move.toRow, move.toColumn);
		if (lfigure != nullptr && lfigure->direction != this->direction) {
			res.Add(move);
		}
	}
	move.toColumn = move.fromColumn;
	move.toRow = this->getNextRow(move.toRow);
	lfigure = lboard->getFigure(move.toRow, move.toColumn);
	if (this->bIsFirstMove && lfigure == nullptr) {
		res.Add(move);
	}
	return res;
}
void APawnFigure::moveTo(int32 row, int32 column) {
	AFigure::moveTo(row, column);
	this->bIsFirstMove = false;
}
int32 APawnFigure::getNextRow(int32 row) const {
	return this->direction == DirectionFigure::WHITE ? row + 1 : row - 1;
}