// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Column.generated.h"

UCLASS()
class CHESS_API AColumn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColumn();
	/**
	 * Устанавливает видимость клетки
	 * @param bIsVisisble - true, если клетка должна быть видима и false - если нет. 
	 */
	UFUNCTION(Client, reliable)
		void SetVisible(bool bIsVisisble);
	/**
	 * Назначает клетке столбец и рядок
	 * @param Row - Рядок клетки
	 * @param Column - Столбец клетки
	 */
	UFUNCTION(Server, reliable)
		void Initialize(int32 Row, int32 Column);

	virtual void Tick(float DeltaTime) override;
	/** Получает рядок клетки */
	int32 GetRowPosition() const;
	/** Получает столбец клетки */
	int32 GetColumnPosition() const;
protected:
	/** Модель клетки */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* CubeMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	/** Рядок клетки */
	UPROPERTY(Replicated)
		int32 RowPosition;
	/** Столбец клетки */
	UPROPERTY(Replicated)
		int32 ColumnPosition;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
