// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionFigure.h"
#include "FMove.h"
#include "Figure.generated.h"

UCLASS()
class CHESS_API AFigure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	FVector target;
	FVector source;
	float time;
	int32 positionRow;
	int32 positionColumn;
	class ABoard* board;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* figure;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TEnumAsByte<DirectionFigure> direction;
	virtual TArray<FMove> getMoves() const;
	virtual void moveTo(int32 row, int32 column);
	int32 getPositionRow() const;
	int32 getPositionColumn() const;
	class ABoard* getBoard() const;
	void initialize(ABoard* board, int32 row, int32 column);
};
