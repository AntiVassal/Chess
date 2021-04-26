#pragma once
#include "FBoardRow.h"
#include "FBoard.generated.h"
USTRUCT()
struct FBoardData {
	GENERATED_BODY()
		//Рядки доски
	UPROPERTY()
	TArray<FBoardRow> rows;
};