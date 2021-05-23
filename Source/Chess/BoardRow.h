#pragma once
#include "BoardColumn.h"
#include "BoardRow.generated.h"
/** Структура, описывающая состояние рядка игровых клеток */
USTRUCT()
struct FBoardRow {
	GENERATED_BODY()
	/** Клетки в рядку */
	UPROPERTY()
	TArray<FBoardColumn> Columns;
};