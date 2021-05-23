// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveLeftDown.generated.h"

/**
 * �������� ������ ����� � ����, �� ���������
 */
UCLASS()
class CHESS_API UMoveLeftDown : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * ��������� ������ ����
	 * @param Length - ������ ���� (1-7)
	 */
	void SetLength(int8 Length);
private:
	/** ������ ���� (1-7) */
	int8 LengthMove;
	
};
