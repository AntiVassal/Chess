#pragma once
#include "BoardRow.h"
#include "BoardState.generated.h"
/** Структура, описывающая состояние доски */
USTRUCT()
struct FBoardState {
	GENERATED_BODY()
	/** Рядки доски */
	UPROPERTY()
	TArray<FBoardRow> Rows;
};