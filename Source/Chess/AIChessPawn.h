// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPawn.h"
#include "ColorFigure.h"
#include "AIChessPawn.generated.h"

/**
 * ���������� ���� � ������������ ����������
 */
UCLASS()
class CHESS_API AAIChessPawn : public AChessPawn
{
	GENERATED_BODY()
public:
protected:
	/** 
	 * ����� ����� �������� ������ �� �������� ����, ����������� ������
	 * @see AChessPawn::WhaitNextMove
	 */
	void WhaitNextMove_Implementation() override;
	/**
	 * ����� ����� ������� �� ���������������� ����� �����, �� �� ������ �������� �����
	 * @param Row - �����, � ������� ���������� �����
	 * @param Column - �������, � ������� ���������� �����
	 * @see AChessPawn::OnPawnEndPath
	 */
	void OnPawnEndPath_Implementation(int32 Row, int32 Column) override;
	void Win_Implementation() override;
	void Lose_Implementation() override;
private:
	/**
	 * ��������� ����� ������ �����
	 * @param Depth - ������� ������, ��� ������ �����, ��� ����� ����� ��. ��������!!! ���� �������� ����� ������ ��������� ���������� ����. �� ������������� ��������� ����� ������ 6
	 * @param ColorFigure - ���� ����� ������, ��� ������� ����� ���������� ������ ���
	 * @param OutMoves - ��������� �� ������, � ������� ����� ��������� ������ ���� 
	 * @return ���������� ��� ���������� �����. �� ����� ������ ��������� ������������ ��������, ��������� ��� ����������� ������ ��� ����������� ������ ������.
	 */
	float Minimax(int32 Depth, EColorFigure ColorFigure, TArray<class UMoveFigure*>* OutMoves);
};
