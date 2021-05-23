#pragma once
#include "CoreMinimal.h"
#include "ColorFigure.generated.h"
/** ������������ ������ ����� */
UENUM(BlueprintType)
enum class EColorFigure : uint8 {
	NONE UMETA(DisplayName = "None"),
	WHITE UMETA(DisplayName = "White"),
	BLACK UMETA(DisplayName = "Black")
};