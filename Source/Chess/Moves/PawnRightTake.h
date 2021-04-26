// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MoveFigure.h"
#include "PawnRightTake.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UPawnRightTake : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool isMoving() override;
	virtual int8 toColumn() const override;
	virtual int8 toRow() const override;
	virtual class AFigure* getDestroyFigure() const override;
};