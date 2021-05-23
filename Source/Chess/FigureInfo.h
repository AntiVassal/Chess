#pragma once
#include "CoreMinimal.h"
#include "FigureInfo.generated.h"
/** Структура, описывающая иформацию о расположении фигуры на доске */
USTRUCT()
struct FFigureInfo {
	GENERATED_BODY()
	/** Рядок фигуры */
	int8 Row;
	/** Столбец фигуры */
	int8 Column;
	/** Количество выполненых ходов */
	int32 CountMoves;
};