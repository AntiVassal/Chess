// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "PawnLeftDiagonal.generated.h"

/**
 * Ход, при котором пешка бьёт фигуру, находящуюся слева по диагонали
 */
UCLASS()
class CHESS_API UPawnLeftDiagonal : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
};
