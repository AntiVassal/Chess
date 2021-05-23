// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveKnight.generated.h"

/**
 * ����������� ������ �� �������� ��������, ��� �������� �� ��, ��������� ����� ������� � ������ ����������� ������ ������.
 */
UCLASS()
class CHESS_API UMoveKnight : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * ��������� ��������, �� ������� ����� ��������� ���
	 * @param Row - �������� �� ��������� (�� -7, �� 7, ��� ����� ����)
	 * @param Column - �������� �� ����������� (�� -7, �� 7, ��� ����� ����)
	 */
	void SetOffset(int8 Row, int8 Column);
private:
	/** �������� �� ��������� */
	int8 OffsetRow;
	/** �������� �� ����������� */
	int8 OffsetColumn;
};
