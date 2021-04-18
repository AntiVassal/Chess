// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DirectionFigure.h"
#include "ChessPawn.generated.h"

UCLASS(config=Game)
class AChessPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing=onDirectionReplicated)
	TEnumAsByte<DirectionFigure> direction;
	UFUNCTION()
	void onDirectionReplicated();
protected:
	virtual void BeginPlay() override;
	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* camera;
private:
	UPROPERTY(Replicated)
	class ABoard* board;
};
