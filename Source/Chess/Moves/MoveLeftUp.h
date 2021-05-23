// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveLeftUp.generated.h"

/**
 * Движение по диагонали влево и вверх
 */
UCLASS()
class CHESS_API UMoveLeftUp : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * Устанавливает длинну хода
	 * @param Length - Длинна хода (количество клеток, 1 - 7)
	 */
	void SetLength(int8 Length);
private:
	/** Длинна хода (количество клеток, 1 - 7) */
	int8 LengthMove;
	
};
