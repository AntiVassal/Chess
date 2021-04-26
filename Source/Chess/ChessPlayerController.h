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
	//����������� ���� � ������� ������
	UFUNCTION(Client, reliable)
	void selectFigureTo(int32 row, int32 column);
	//���������� �������� ������
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	//������ ��������
	UPROPERTY()
		TSubclassOf<class UUserWidget> winUMG;
	//������ ���������
	UPROPERTY()
		TSubclassOf<class UUserWidget> loseUMG;
protected:
	//���������� ������� �����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 _row;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 _column;
	//���������� ������������ �������
	UPROPERTY()
		class UUserWidget* CurrentWidget;
private:
	//������ ������ ������
	UPROPERTY()
		TSubclassOf<class UUserWidget> selectedFigureUMG;
	//������ �������� ����
	UPROPERTY()
		TSubclassOf<class UUserWidget> mainMenuUMG;
};


