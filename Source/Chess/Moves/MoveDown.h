// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveDown.generated.h"

/**
 * �������� ���� �� �������� ������.
 */
UCLASS()
class CHESS_API UMoveDown : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * ������������� ������, �� ������� ����� ��������� ���
	 * @param Length - ������ ����
	 */
	void SetLength(int8 Length);
private:
	/** ������ ���� */
	int8 LengthMove;
};
