// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "PawnForwardOneStep.generated.h"

/**
 * Движение пешки вперёд на одну клетку
 */
UCLASS()
class CHESS_API UPawnForwardOneStep : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
};
