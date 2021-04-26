#pragma once
#include "CoreMinimal.h"
#include "FBoardColumn.generated.h"
USTRUCT()
struct FBoardColumn {
	GENERATED_BODY()
		//Фигура размещщённая в клетке
	UPROPERTY()
	class AFigure* figure;
	//Количество ходов, выполненых даной фигурой
	UPROPERTY()
	int32 countMoves;
};