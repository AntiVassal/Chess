// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MoveFigure.h"
#include "MoveDown.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMoveDown : public UMoveFigure
{
	GENERATED_BODY()
public:
	//Проверка возможен ли ход
	virtual bool isMoving() override;
	//Получение столпца назначения
	virtual int8 toColumn() const override;
	//Получение рядка назначения
	virtual int8 toRow() const override;
	//Установка длинны, на которую будет произведён ход
	void setCount(int8 count);
private:
	//Длинна хода
	int8 _count;
};
