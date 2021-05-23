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
	 * ������������� ��������� ������
	 * @param bIsVisisble - true, ���� ������ ������ ���� ������ � false - ���� ���. 
	 */
	UFUNCTION(Client, reliable)
		void SetVisible(bool bIsVisisble);
	/**
	 * ��������� ������ ������� � �����
	 * @param Row - ����� ������
	 * @param Column - ������� ������
	 */
	UFUNCTION(Server, reliable)
		void Initialize(int32 Row, int32 Column);

	virtual void Tick(float DeltaTime) override;
	/** �������� ����� ������ */
	int32 GetRowPosition() const;
	/** �������� ������� ������ */
	int32 GetColumnPosition() const;
protected:
	/** ������ ������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* CubeMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	/** ����� ������ */
	UPROPERTY(Replicated)
		int32 RowPosition;
	/** ������� ������ */
	UPROPERTY(Replicated)
		int32 ColumnPosition;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
