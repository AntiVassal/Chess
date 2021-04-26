// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DirectionFigure.h"
#include "Figure.h"
#include "ChessPawn.generated.h"

UCLASS(config=Game)
class AChessPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//���� �����, �� ������� ������ �����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing=onDirectionReplicated)
	TEnumAsByte<DirectionFigure> direction;
	//������� ����������� ������ ���, ����� ���������� direction �������������
	UFUNCTION()
	void onDirectionReplicated();
	//���������� ��������� � ��������
	UFUNCTION(Client, reliable)
		void win();
	//����������� ��������� � ���������
	UFUNCTION(Client, reliable)
		void lose();
	//��������, ��� ���� �� ����� ��������� �� ���������������� ����� ����� � �������� � �� ���� �� ��������� �����
	UFUNCTION(Server, reliable)
		void pawnEndPath(int32 row, int32 column);
	//�������� ����
	UFUNCTION(Server, reliable)
		void whaitMove();
	//���������� ����� �� ����� � ����������� �� ����, �� ����� ���� ������ �����
	UFUNCTION(BlueprintCallable)
		void selectedFigureSwap(TSubclassOf<AFigure> whiteFigure, TSubclassOf<AFigure> blackFigure, int32 row, int32 column);
protected:
	virtual void BeginPlay() override;
	//������� �����
	void TriggerClick();
	//���������� ����
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* camera;
	//������ �����
	UPROPERTY(Replicated)
		class ABoard* board;
private:
	//���� �� ����� ��� ������
	UFUNCTION(Server, reliable)
		void clickToBoard(FHitResult HitResult);
	//���������� ������ � �������� ������
	UFUNCTION(Server, reliable)
		void swapPawnToFigure(TSubclassOf<AFigure> figure, int32 row, int32 column);
	//���� �� ����� ��� ������ (����������� ��������� �����)
	UFUNCTION(Client, reliable)
		void clickToBoardClient(FHitResult HitResult);
	//��������� ������
	class AFigure* selectedFigure;
};
