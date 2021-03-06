// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChessGameMode();
protected:
	virtual void BeginPlay() override;
};



