#pragma once
#include "FBoardColumn.h"
#include "FBoardRow.generated.h"
USTRUCT()
struct FBoardRow {
	GENERATED_BODY()
		//������ � �����
	UPROPERTY()
	TArray<FBoardColumn> columns;
};