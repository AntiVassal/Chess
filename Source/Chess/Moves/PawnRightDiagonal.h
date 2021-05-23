// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "PawnRightDiagonal.generated.h"

/**
 * Ход, при котором пешка бьёт фигуру, находящуюся справа по диагонали
 */
UCLASS()
class CHESS_API UPawnRightDiagonal : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
};
