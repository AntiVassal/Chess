// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FColumnBoard.h"
#include "DirectionFigure.h"
#include "Board.generated.h"

UCLASS()
class CHESS_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* board;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* pawnWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* pawnBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* rockWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* rockBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* knightWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* knightBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* bishopWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* bishopBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* queenWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* queenBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* kingWhite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* kingBlack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* cube;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* color;
	FColumnBoard getColumn(int32 row, int32 column) const;
	void selectFigure(int32 row, int32 column, DirectionFigure direction);
	void click(FVector point);
	void destroyFigure(class AFigure* figure);
	AFigure* getFigure(int32 row, int32 column) const;
	UFUNCTION(Server, Reliable)
	void initializePawn(class AChessPawn* pawn);
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	AChessPawn* white = nullptr;
	AChessPawn* black = nullptr;
	AFigure* selectedFigure = nullptr;
	void moveFigureTo(AFigure* figure, int32 row, int32 column);
	TArray<FColumnBoard> columns;
	TArray<AFigure*> figures;
	void spawnFigure(UClass* figure, int32 row, int32 column, FRotator rotator);
};
