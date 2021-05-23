// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "King.generated.h"

/**
 * ќписываетс€ фигура корол€
 */
UCLASS()
class CHESS_API AKing : public AFigure
{
	GENERATED_BODY()
public:
	AKing();
	/**
	 * ѕровер€т, находитс€ ли король под прицелом другой фигуры, или нет
	 * @return true 
	 * @return false 
	 */
	bool IsCheck() const;
protected:
	float GetPower(int8 Row, int8 Column) const override;
private:
	/** ћатрица модификаторов веса фигуры, в зависимости от того, где расположена фигура */
	const float PowerMatrix[8][8] = {
		{2.0f, 3.0f, 1.0f, 0.0f, 0.0f, 1.0f, 3.0f, 2.0f},
		{2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f},
		{-1.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -1.0f},
		{-2.0f, -3.0f, -3.0f, -4.0f, -4.0f, -3.0f, -3.0f, -2.0f},
		{-3.0f, -4.0f, -4.0f, -5.0f, -5.0f, -4.0f, -4.0f, -3.0f},
		{-3.0f, -4.0f, -4.0f, -5.0f, -5.0f, -4.0f, -4.0f, -3.0f},
		{-3.0f, -4.0f, -4.0f, -5.0f, -5.0f, -4.0f, -4.0f, -3.0f},
		{-3.0f, -4.0f, -4.0f, -5.0f, -5.0f, -4.0f, -4.0f, -3.0f}
	};
};
