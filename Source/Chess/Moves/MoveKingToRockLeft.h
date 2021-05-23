// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveKingToRockLeft.generated.h"

/**
 * Рокировка с левой башней
 */
UCLASS()
class CHESS_API UMoveKingToRockLeft : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual void Move() override;
	virtual void Rollback() override;
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	virtual void FinishMove();
};
