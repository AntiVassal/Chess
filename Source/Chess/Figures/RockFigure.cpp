// Fill out your copyright notice in the Description page of Project Settings.


#include "RockFigure.h"
#include "../Board.h"
#include "../Moves/MoveUp.h"
#include "../Moves/MoveDown.h"
#include "../Moves/MoveLeft.h"
#include "../Moves/MoveRight.h"
ARockFigure::ARockFigure() {
	for (int8 i = 1; i < 8; ++i) {
		//Движение вверх на i клеток
		FString Name = TEXT("MoveUp");
		Name.AppendInt(i);
		UMoveUp* MoveUp = this->CreateDefaultSubobject<UMoveUp>(FName(Name));
		MoveUp->SetLength(i);
		this->RegisterMove(MoveUp);
		//Движение вниз на i клеток
		Name = TEXT("MoveDown");
		Name.AppendInt(i);
		UMoveDown* MoveDown = this->CreateDefaultSubobject<UMoveDown>(FName(Name));
		MoveDown->SetLength(i);
		this->RegisterMove(MoveDown);
		//Движение влево на i клеток
		Name = TEXT("MoveLeft");
		Name.AppendInt(i);
		UMoveLeft* MoveLeft = this->CreateDefaultSubobject<UMoveLeft>(FName(Name));
		MoveLeft->SetLength(i);
		this->RegisterMove(MoveLeft);
		//Движение вправо на i клеток
		Name = TEXT("MoveRight");
		Name.AppendInt(i);
		UMoveRight* MoveRight = this->CreateDefaultSubobject<UMoveRight>(FName(Name));
		MoveRight->SetLength(i);
		this->RegisterMove(MoveRight);
	}
}
float ARockFigure::GetPower(int8 Row, int8 Column) const {
	if (this->GetColor() == EColorFigure::BLACK) {
		Row = 7 - Row;
	}
	return 50.0f + PowerMatrix[Row][Column];
}