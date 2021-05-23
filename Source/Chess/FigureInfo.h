#pragma once
#include "CoreMinimal.h"
#include "FigureInfo.generated.h"
/** ���������, ����������� ��������� � ������������ ������ �� ����� */
USTRUCT()
struct FFigureInfo {
	GENERATED_BODY()
	/** ����� ������ */
	int8 Row;
	/** ������� ������ */
	int8 Column;
	/** ���������� ���������� ����� */
	int32 CountMoves;
};