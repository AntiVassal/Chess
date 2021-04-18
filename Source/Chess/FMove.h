#pragma once
#include "CoreMinimal.h"
#include "FMove.generated.h"
USTRUCT(BlueprintType)
struct FMove {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 fromRow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 fromColumn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 toRow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 toColumn;
};