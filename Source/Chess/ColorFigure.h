#pragma once
#include "CoreMinimal.h"
#include "ColorFigure.generated.h"
/** Перечисление цветов фигур */
UENUM(BlueprintType)
enum class EColorFigure : uint8 {
	NONE UMETA(DisplayName = "None"),
	WHITE UMETA(DisplayName = "White"),
	BLACK UMETA(DisplayName = "Black")
};