// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveFigure.h"
#include "MoveKnight.generated.h"

/**
 * Перемещение фигуры на указаное смещение, без проверки на то, находятся между началом и концом перемещения другие фигуры.
 */
UCLASS()
class CHESS_API UMoveKnight : public UMoveFigure
{
	GENERATED_BODY()
public:
	virtual bool IsValidMoving() override;
	virtual FFigureInfo GetFigureInfoAfterMoving() const override;
	/**
	 * Установка смещения, на которое будет произведён ход
	 * @param Row - Смещение по вертикали (от -7, до 7, без учёта нуля)
	 * @param Column - Смещение по горизонтали (от -7, до 7, без учёта нуля)
	 */
	void SetOffset(int8 Row, int8 Column);
private:
	/** Смещение по вертикали */
	int8 OffsetRow;
	/** Смещение по горизонтали */
	int8 OffsetColumn;
};
