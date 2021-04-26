// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MoveFigure.h"
#include "MoveKnight.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMoveKnight : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool isMoving() override;
	virtual int8 toColumn() const override;
	virtual int8 toRow() const override;
	//Установка смещения, на которое будет произведён ход
	void setOffset(int8 row, int8 column);
private:
	int8 _offsetRow;
	int8 _offsetColumn;
};
