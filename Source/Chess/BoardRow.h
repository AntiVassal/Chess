#pragma once
#include "BoardColumn.h"
#include "BoardRow.generated.h"
/** ���������, ����������� ��������� ����� ������� ������ */
USTRUCT()
struct FBoardRow {
	GENERATED_BODY()
	/** ������ � ����� */
	UPROPERTY()
	TArray<FBoardColumn> Columns;
};