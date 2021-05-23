// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "Knight.generated.h"

/**
 * ����������� ������ ������
 */
UCLASS()
class CHESS_API AKnight : public AFigure
{
	GENERATED_BODY()
public:
	AKnight();
protected:
	float GetPower(int8 Row, int8 Column) const override;
private:
	/** ������� ������������� ���� ������, � ����������� �� ����, ��� ����������� ������ */
	const float PowerMatrix[8][8] = {
		{-5.0f, -4.0f, -3.0f, -3.0f, -3.0f, -3.0f, -4.0f, -5.0f},
		{-4.0f, -2.0f, 0.0f, 0.5f, 0.5f, 0.0f, -2.0f, -4.0f},
		{-3.0f, 0.5f, 1.0f, 1.5f, 1.5f, 1.0f, 0.5f, -3.0f},
		{-3.0f, 0.0f, 1.5f, 2.0f, 2.0f, 1.5f, 0.0f, -3.0f},
		{-3.0f, 0.5f, 1.5f, 2.0f, 2.0f, 1.5f, 0.5f, -3.0f},
		{-3.0f, 0.0f, 1.0f, 1.5f, 1.5f, 1.0f, 0.0f, -3.0f},
		{-4.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, -2.0f, -4.0f},
		{-5.0f, -4.0f, -3.0f, -3.0f, -3.0f, -3.0f, -4.0f, -5.0f}
	};
};
