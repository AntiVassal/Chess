// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "PawnFigure.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API APawnFigure : public AFigure
{
	GENERATED_BODY()
private:
	uint8 bIsFirstMove : 1;
	int32 getNextRow(int32 row) const;
public:
	APawnFigure();
	virtual TArray<FMove> getMoves() const override;
	virtual void moveTo(int32 row, int32 column) override;
	uint8 isFirstMove() const;
};
