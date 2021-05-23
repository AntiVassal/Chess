// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveDown.generated.h"

/**
 * Движение вниз на указаную длинну.
 */
UCLASS()
class CHESS_API UMoveDown : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * Устанавливает длинну, на которую будет произведён ход
	 * @param Length - Длинна хода
	 */
	void SetLength(int8 Length);
private:
	/** Длинна хода */
	int8 LengthMove;
};
