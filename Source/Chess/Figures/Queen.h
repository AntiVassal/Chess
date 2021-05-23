// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "Queen.generated.h"

/**
 * Описывается ферзь
 */
UCLASS()
class CHESS_API AQueen : public AFigure
{
	GENERATED_BODY()
public:
	AQueen();
protected:
	float GetPower(int8 Row, int8 Column) const override;
private:
	/** Матрица модификаторов веса фигуры, в зависимости от того, где расположена фигура */
	const float PowerMatrix[8][8] = {
		{-2.0f, -1.0f, -1.0f, -0.5f, -2.0f, -1.0f, -1.0f, -0.5f},
		{-1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},
		{-1.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, -1.0f},
		{0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, -0.5f},
		{-0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, -0.5f},
		{-1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, -1.0f},
		{-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},
		{-2.0f, -1.0f, -1.0f, -0.5f, -2.0f, -1.0f, -1.0f, -0.5f}
	};
};
