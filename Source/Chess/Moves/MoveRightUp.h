// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveRightUp.generated.h"

/**
 * Движение по диагонали, вправо и вверх
 */
UCLASS()
class CHESS_API UMoveRightUp : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * Установка длинны хода
	 * @param Length - Длинна хода в клетках (1-7)
	 */
	void SetLength(int8 Length);
private:
	/** Длинна хода в клетках (1-7) */
	int8 LengthMove;
};
