#pragma once
#include "FBoardRow.h"
#include "FBoard.generated.h"
USTRUCT()
struct FBoardData {
	GENERATED_BODY()
		//����� �����
	UPROPERTY()
	TArray<FBoardRow> rows;
};