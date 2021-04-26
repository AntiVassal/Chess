#pragma once
#include "CoreMinimal.h"
#include "FBoardColumn.generated.h"
USTRUCT()
struct FBoardColumn {
	GENERATED_BODY()
		//������ ������������ � ������
	UPROPERTY()
	class AFigure* figure;
	//���������� �����, ���������� ����� �������
	UPROPERTY()
	int32 countMoves;
};