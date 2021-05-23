#pragma once
#include "CoreMinimal.h"
#include "BoardColumn.generated.h"
/** Структура, описывающая состояние игровой клетки */
USTRUCT()
struct FBoardColumn {
	GENERATED_BODY()
	/** Фигура размещщённая в клетке */
	UPROPERTY()
	class AFigure* Figure;
	/** Количество ходов, выполненых даной фигурой */
	UPROPERTY()
	int32 CountMoves;
};