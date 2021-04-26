#pragma once
#include "FBoardColumn.h"
#include "FBoardRow.generated.h"
USTRUCT()
struct FBoardRow {
	GENERATED_BODY()
		//Клетки в рядку
	UPROPERTY()
	TArray<FBoardColumn> columns;
};