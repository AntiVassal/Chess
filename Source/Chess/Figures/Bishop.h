// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "Bishop.generated.h"

/** Класс, описывающий офицера */
UCLASS()
class CHESS_API ABishop : public AFigure
{
	GENERATED_BODY()
public:
	ABishop();
	virtual float GetPower(int8 row, int8 column) const override;
protected:
private:
	/** Матрица модификаторов веса фигуры, в зависимости от того, где расположена фигура */
	const float PowerMatrix[8][8] = {
		{-2.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -2.0f},
		{-1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, -1.0f},
		{-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f},
		{-1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f},
		{-1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.5f, 0.5f, -1.0f},
		{-1.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.5f, 0.0f, -1.0f},
		{-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},
		{-2.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -2.0f}
	};
};
