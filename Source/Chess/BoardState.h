#pragma once
#include "BoardRow.h"
#include "BoardState.generated.h"
/** ���������, ����������� ��������� ����� */
USTRUCT()
struct FBoardState {
	GENERATED_BODY()
	/** ����� ����� */
	UPROPERTY()
	TArray<FBoardRow> Rows;
};