// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "RockFigure.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ARockFigure : public AFigure
{
	GENERATED_BODY()
public:
	ARockFigure();
	float getPower(int8 row, int8 column) const override;
private:
	//ћатрица модификаторов веса фигуры, в зависимости от того, где расположена фигура
	const float powerMatrix[8][8] = {
		{0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f},
		{-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f},
		{-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f},
		{-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f},
		{-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f},
		{-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f},
		{0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f},
		{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
	};
};
