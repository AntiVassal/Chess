// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../FigureInfo.h"
#include "MoveFigure.generated.h"

/**
 * �����, ����� ��� ���� �����.
 */
UCLASS()
class CHESS_API UMoveFigure : public UObject
{
	GENERATED_BODY()
public:
	/**
	 * ���������, ������������� �� ������� ��� �������� ����, ��� ���.
	 * @return true ��� ������������� ��������.
	 * @return false ��� �� ������������� ��������, ���� ������� �� ������� ������� �����. ���������� ���� ����������. 
	 */
	virtual bool IsValidMoving();
	/** ���������� ������ �� ������� ����� (��� �������� ��������� �����������, ���� ��� ��������) */
	virtual void Move();
	/**
	 * ���������� ������� ����� �� ���� ���������, ������� ���� ��� �� ������ ����.
	 * @waring �������� ������ ��� ���������� ���������. ���� ��������� ���������, �� ������ �� ������.
	 */
	virtual void Rollback();
	/**
	 * ������������� ��������� ������ �� ������� �����, ����� ����, ��� ��� ����� ��������.
	 * @return ���������, ����������� ��������� ������, � ���������� ���������� �����.
	 */
	virtual FFigureInfo GetFigureInfoAfterMoving() const;
	/**
	 * �������� �������� ��������� ������ �� ������� ����� �� ���������� ����
	 * @return ���������, ����������� ��������� ������, � ���������� ���������� �����.
	 * @warning ����� ���������� ����, ������� ����� ���������� �������� ��������� ������, � �� ��������� ������ �� ���������� ����.
	 */
	virtual FFigureInfo GetFigureInfoBeforeMoving() const;
	/**
	 * �������� ������, ������� ����� ���������� �� ����� ���������� ����
	 * @return ��������� �� ������, ������� ����� ����������.
	 */
	virtual class AFigure* GetDestroyFigure() const;
	/**
	 * �������� � ���, ��� ��� ��������, � ��������� ����� ������ (���� ��������� ���������, �� ���������� ����� ���������� �������� �����������).
	 * @warning ���������� ��� ���������� �������� �����������, � �������� ������ ��� ����������� ���������.
	 */
	virtual void FinishMove();
	/**
	 * ��������� �������� ������, ������� ����� ������������
	 * @return ��������� �� ������.
	 */
	class AFigure* GetFigure() const;
	/**
	 * ��������� ��������� �� ������, ������� ����� ������������.
	 * @param Figure ��������� �� ������
	 * @warning ����� ���������� ������ ��� ����������� ����, � ������� �������� ��� �������
	 */
	void Initialzie(class AFigure* Figure);
private:
	/** ��������� �� ������, ������� ����� ������������ */
	class AFigure* FigureActor;
};
