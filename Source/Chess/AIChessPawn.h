// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPawn.h"
#include "DirectionFigure.h"
#include "AIChessPawn.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AAIChessPawn : public AChessPawn
{
	GENERATED_BODY()
public:
protected:
	//��� �������� ���� �� ��, ���� ��� ����� ��������������
	void whaitMove_Implementation() override;
	void pawnEndPath_Implementation(int32 row, int32 column) override;
	void win_Implementation() override;
	void lose_Implementation()override;
private:
	//������� ������ ������ �����
	float minimax(int32 depth, DirectionFigure figureDirection, TArray<class UMoveFigure*>* move);
};
