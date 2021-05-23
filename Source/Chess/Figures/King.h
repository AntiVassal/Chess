// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Figure.h"
#include "King.generated.h"

/**
 * ����������� ������ ������
 */
UCLASS()
class CHESS_API AKing : public AFigure
{
	GENERATED_BODY()
public:
	AKing();
	/**
	 * ��������, ��������� �� ������ ��� �������� ������ ������, ��� ���
	 * @return true 
	 * @return false 
	 */
	bool IsCheck() const;
protected:
	float GetPower(int8 Row, int8 Column) const override;
private:
	/** ������� ������������� ���� ������, � ����������� �� ����, ��� ����������� ������ */
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
