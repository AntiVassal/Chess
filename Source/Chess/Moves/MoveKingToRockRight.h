// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MoveFigure.h"
#include "MoveKingToRockRight.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMoveKingToRockRight : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool isMoving() override;
	virtual void move() override;
	virtual void rollback() override;
	virtual int8 toColumn() const override;
	virtual int8 toRow() const override;
	virtual void finishMove();
};
