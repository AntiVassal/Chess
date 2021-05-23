// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ColorFigure.h"
#include "Figure.generated.h"
/** �����, ����������� ������ ������ */
UCLASS()
class CHESS_API AFigure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigure();

protected:
	/** ������ ������ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* FigureMesh;
	/** ���� ������ (������ ��� �����) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EColorFigure Color;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	 * ����� ������������ ��������� ����
	 * @param Move - ��������� ���� 
	 */
	void RegisterMove(class UMoveFigure* Move);
private:
	/** ���������� ��������� �� �����. ����� ��� ���������� ������ ������� ������ */
	UPROPERTY(Replicated)
	class ABoard* BoardActor;
	/** ������ ���� ����������������� ����� */
	UPROPERTY()
	TArray<class UMoveFigure*> Moves;
	/** �������� ��������������, ���� ����� ����������� ������ �� ����� ���� (����� ��� ������ �������� �����������) */
	FVector TargetMoveAnimation;
	/** �������� �������������� ������ �� ������ ����������� (����� ��� ������ �������� �����������) */
	FVector SourceMoveAnimation;
	/** ����� ��������������� �������� (0 - �������� ��� �� ��������, 1 - �������� �����������) */
	float TimeAnimationExecuted;
	/** ���� true - ������ �������� ��������� � ����� �������� ����, ��� ��� �������� */
	bool bEndMove;
	/** ��������� �� ��������� ���. ����� ��� ����, ����� �������� ���� � ���, ��� �� ��������. */
	class UMoveFigure* LastMove;
public:
	/**
	 * ������� ������������� �������� �����������
	 * @param Move - ��������� ����, ����������� �����������
	 */
	UFUNCTION(Server, reliable)
	virtual void AnimateMove(class UMoveFigure* Move);
	/**
	 * ��������� ��������� �� �����, � ��������� ����.
	 * @param Board - ��������� �� �����
	 * @warning - ���������� �� ������ ����� �� ����� ������. � ������ ������� �������� �� �����. 
	 */
	UFUNCTION(Server, reliable)
	void Initialize(ABoard* Board);
	/** �������� ����������� � �������� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedMoveFigure = 1.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/**
	 * �������� ��� ���� ������, ������� ������������� ��������.
	 * @param OutMoves - ������ �� ������, � ������� ����� �������� ����
	 */
	virtual void GetMoves(TArray<class UMoveFigure*>& OutMoves);
	/**
	 * �������� ���� ������
	 * @return ������� ������������, ������� ���������� ���� ������. (EColorFigure::WHITE - ��� ����� � EColorFigure::BLACK - ��� ������)
	 */
	EColorFigure GetColor() const;
	/**
	 * �������� ��������� �� ������� �����
	 * @return ��������� �� ������� �����
	 */
	class ABoard* GetBoard() const;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/**
	 * �������� ���� ������, � ����������� �� ������������ �� ������� �����
	 * @param Row - �����, � ������� ����������� ������
	 * @param Column - �������, � ������� ����������� ������
	 * @return ���� ������
	 */
	virtual float GetPower(int8 Row, int8 Column) const;
};
