#pragma once
#include "CoreMinimal.h"
#include "FColumnBoard.generated.h"
USTRUCT(BlueprintType)
struct FColumnBoard
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* column;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector location;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector bounds;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 rowIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 columnIndex;
};

