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
	//Устанавливает видимость клетки
	UFUNCTION(Client, reliable)
		void setVisible(bool isVisisble);
	//Назначает клетке столбец и рядок
	UFUNCTION(Server, reliable)
		void initialize(int32 row, int32 column);

	virtual void Tick(float DeltaTime) override;
	//Получает рядок клетки
	int32 getRowPosition() const;
	//Получает столбец клетки
	int32 getColumnPosition() const;
protected:
	//Модель клетки
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* cube;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	//Рядок клетки
	UPROPERTY(Replicated)
		int32 rowPosition;
	//Столбец клетки
	UPROPERTY(Replicated)
		int32 columnPosition;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
