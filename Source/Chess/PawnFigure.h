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
	//ћатрица модификаторов веса фигуры, в зависимости от того, где расположена фигура
	const float powerMatrix[8][8] = {
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
	float getPower(int8 row, int8 column) const override;
public:
	APawnFigure();
	void moveTo_Implementation(class UMoveFigure* move) override;
};
