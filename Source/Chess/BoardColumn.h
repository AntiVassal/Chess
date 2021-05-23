#pragma once
#include "CoreMinimal.h"
#include "BoardColumn.generated.h"
/** ���������, ����������� ��������� ������� ������ */
USTRUCT()
struct FBoardColumn {
	GENERATED_BODY()
	/** ������ ������������ � ������ */
	UPROPERTY()
	class AFigure* Figure;
	/** ���������� �����, ���������� ����� ������� */
	UPROPERTY()
	int32 CountMoves;
};