// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"
#include "../Board.h"
#include "../Moves/MoveUp.h"
#include "../Moves/MoveDown.h"
#include "../Moves/MoveLeft.h"
#include "../Moves/MoveRight.h"
#include "../Moves/MoveLeftUp.h"
#include "../Moves/MoveRightUp.h"
#include "../Moves/MoveRightDown.h"
#include "../Moves/MoveLeftDown.h"
float AQueen::GetPower(int8 Row, int8 Column) const {
	if (this->GetColor() == EColorFigure::BLACK) {
		Row = 7 - Row;
	}
	return 90.0f + PowerMatrix[Row][Column];
}
AQueen::AQueen() {
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
		//Ход влево и верх по диагонали на i клеток
		Name = TEXT("MoveLeftUp");
		Name.AppendInt(i);
		UMoveLeftUp* LeftUp = this->CreateDefaultSubobject<UMoveLeftUp>(FName(Name));
		LeftUp->SetLength(i);
		this->RegisterMove(LeftUp);
		//Ход вправо и верх по диагонали на i клеток
		Name = TEXT("MoveRightUp");
		Name.AppendInt(i);
		UMoveRightUp* RightUp = this->CreateDefaultSubobject<UMoveRightUp>(FName(Name));
		RightUp->SetLength(i);
		this->RegisterMove(RightUp);
		//Ход вправо и низ по диагонали на i клеток
		Name = TEXT("MoveRightDown");
		Name.AppendInt(i);
		UMoveRightDown* RightDown = this->CreateDefaultSubobject<UMoveRightDown>(FName(Name));
		RightDown->SetLength(i);
		this->RegisterMove(RightDown);
		//Ход влево и низ по диагонали на i клеток
		Name = TEXT("MoveLeftDown");
		Name.AppendInt(i);
		UMoveLeftDown* LeftDown = this->CreateDefaultSubobject<UMoveLeftDown>(FName(Name));
		LeftDown->SetLength(i);
		this->RegisterMove(LeftDown);
	}
}