// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "PawnFigure.generated.h"

/**
 * Описывается пешка
 */
UCLASS()
class CHESS_API APawnFigure : public AFigure
{
	GENERATED_BODY()
private:
	/** Матрица модификаторов веса фигуры, в зависимости от того, где расположена фигура */
	const float PowerMatrix[8][8] = {
		{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		{0.5f, 1.0f, 1.0f, -2.0f, -2.0f, 1.0f, 1.0f, 0.5f},
		{0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f, -0.5f, 0.5f},
		{0.0f, 0.0f, 0.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f},
		{0.5f, 0.5f, 1.0f, 2.5f, 2.5f, 1.0f, 0.5f, 0.5f},
		{1.0f, 1.0f, 2.0f, 3.0f, 3.0f, 2.0f, 1.0f, 1.0f},
		{5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f},
		{78.0f, 79.0f, 79.0f, 79.5f, 79.5f, 79.0f, 79.0f, 78.0f}
	};
protected:
	float GetPower(int8 Row, int8 Column) const override;
public:
	APawnFigure();
	void AnimateMove_Implementation(class UMoveFigure* Move) override;
};
