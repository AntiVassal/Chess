// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ColorFigure.h"
#include "Figures/Figure.h"
#include "ChessPawn.generated.h"

UCLASS(config=Game)
class AChessPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	/** ���� �����, �� ������� ������ ����� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing= OnDirectionReplicated)
	EColorFigure ColorSide;
	/** ����������, ��� ������������� ������ � ����������� ����, �� ����� �� ������ �� ����� ������ */
	UFUNCTION()
	void OnDirectionReplicated();
	/** �������� ������, ��� �� ������� */
	UFUNCTION(Client, reliable)
		void Win();
	/** �������� ������, ��� �� �������� */
	UFUNCTION(Client, reliable)
		void Lose();
	/** ��������, ��� ���� �� ����� ��������� �� ���������������� ����� �����, ����� �������� � �� ���� �� ��������� ����� */
	UFUNCTION(Server, reliable)
		void OnPawnEndPath(int32 Row, int32 Column);
	/** �������� ������, ��� ������ ��� ��� */
	UFUNCTION(Server, reliable)
		void WhaitNextMove();
	/**
	 * ��������� ���� �� �������� ����� �� �����, � ����������� �� ����� ������
	 * @param WhiteFigure - �������� ������ ��� ������ �����
	 * @param BlackFigure - �������� ������ ��� ������� �����
	 * @param Row - �����, � ������� ����� ��������� ������
	 * @param Column - �������, � ������� ����� ��������� ������
	 */
	UFUNCTION(BlueprintCallable)
		void SelectedFigureSwap(TSubclassOf<AFigure> WhiteFigure, TSubclassOf<AFigure> BlackFigure, int32 Row, int32 Column);
protected:
	virtual void BeginPlay() override;
	/** �������� � ���, ��� ����� ������� �� ����� */
	void TriggerClick();
	/**
	 * ���������� ����, ��� ����������� ����, ���� ������ ������� �����
	 * @param Start - ������ ����
	 * @param End - ����� ����
	 * @param bDrawDebugHelpers - ����������, ����� �� ������� ��� ��� ���.
	 */
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	/** ������, ����� ������� ����� ����� ������ ������� ����� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* CameraComponent;
	/** ��������� �� ������� ����� */
	UPROPERTY(Replicated)
		class ABoard* BoardActor;
private:
	/**
	 * ����������, ����� ���� ���������� ������������ � ������ ��� �������. ������ ���� ��������� ��������� ������, ���� ���������� �������� ������ � �������� ��������������
	 * @param HitResult - ���������� � �����, ���� ������� �����
	 */
	UFUNCTION(Server, reliable)
		void OnClickToBoard(FHitResult HitResult);
	/**
	 * ������� � ��������� ������ �� ������� �����
	 * @param Figure - ����� ������, ������� ����� ���������� �� �����
	 * @param Row - �����, � ������� ������ ����� ���������
	 * @param Column - �������, � ������� ������ ����� ���������
	 */
	UFUNCTION(Server, reliable)
		void SwapPawnToFigure(TSubclassOf<AFigure> Figure, int32 Row, int32 Column);
	/**
	 * ����������, ����� ���� ���������� ������������ � ������� � ������������ ��� ��������� ���� �������� ������
	 * @param HitResult - ���������� � �����, ���� ������� �����
	 */
	UFUNCTION(Client, reliable)
		void OnClickToBoardClient(FHitResult HitResult);
	/** ��������� �� ������, ������� ����� ������ */
	class AFigure* SelectedFigure;
};
