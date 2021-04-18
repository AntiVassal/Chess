#pragma once
#include "CoreMinimal.h"
#include "DirectionFigure.generated.h"
UENUM(BlueprintType)
enum DirectionFigure {
	NONE UMETA(DisplayName = "None"),
	WHITE UMETA(DisplayName = "White"),
	BLACK UMETA(DisplayName = "Black")
};