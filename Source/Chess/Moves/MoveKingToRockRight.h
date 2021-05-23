// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveKingToRockRight.generated.h"

/**
 * ��������� � ������ ������
 */
UCLASS()
class CHESS_API UMoveKingToRockRight : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual void Move() override;
	virtual void Rollback() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	virtual void FinishMove();
};
