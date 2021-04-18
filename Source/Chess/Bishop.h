// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "Bishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ABishop : public AFigure
{
	GENERATED_BODY()
		virtual TArray<FMove> getMoves() const override;
private:
	bool isValid(int32 row, int32 column, bool& canBrake) const;
};
