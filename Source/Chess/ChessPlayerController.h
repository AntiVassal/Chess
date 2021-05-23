// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChessPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AChessPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AChessPlayerController();
	virtual void BeginPlay() override;
	/**
	 * ���������� ����, � ������� ������, ������� ����� ��������� ������ �����
	 * @param Row - �����, � ������� ���������� �����, �������� �� ����� �����
	 * @param Column - �������, � ������� ���������� �����, �������� �� ����� �����
	 */
	UFUNCTION(Client, reliable)
	void SelectFigureTo(int32 Row, int32 Column);
	/**
	 * �������� ��������� ������ �� ���, ������� �� ��������
	 * @param NewWidgetClass - ������, ������� ����� ����������
	 */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	/** ������ �������� */
	UPROPERTY()
		TSubclassOf<class UUserWidget> WinUMG;
	/** ������ ��������� */
	UPROPERTY()
		TSubclassOf<class UUserWidget> LoseUMG;
protected:
	/** ����� �����, ������� ����� �� ����� ����� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 RowPawnFigure;
	/** ������� �����, ������� ����� �� ����� ����� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ColumnPawnFigure;
	/** ��������� �� ������, ������� ������ ������������ �� ������ */
	UPROPERTY()
		class UUserWidget* CurrentWidget;
private:
	/** ������ ������ ������, �� ����� ����� */
	UPROPERTY()
		TSubclassOf<class UUserWidget> SelectedFigureUMG;
	/** ������ �������� ���� */
	UPROPERTY()
		TSubclassOf<class UUserWidget> MainMenuUMG;
};


