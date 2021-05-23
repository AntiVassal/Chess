// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "PawnLeftTake.generated.h"

/**
 * ’од по диагонали влево на клетку, которую перепрыгнула пешка притивника, при ходе на две клетки вперЄд.
 * ѕри выполнении хода, пешка противника будет уничтожена
 */
UCLASS()
class CHESS_API UPawnLeftTake : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	virtual class AFigure* GetDestroyFigure() const override;
};
