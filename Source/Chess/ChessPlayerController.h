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
	//Отображение меню с выбором фигуры
	UFUNCTION(Client, reliable)
	void selectFigureTo(int32 row, int32 column);
	//Отобразить указаный виджет
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	//Виджет выиграша
	UPROPERTY()
		TSubclassOf<class UUserWidget> winUMG;
	//Виджет проигрыша
	UPROPERTY()
		TSubclassOf<class UUserWidget> loseUMG;
protected:
	//Сохранение позиции пешки
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 _row;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 _column;
	//Сохранение отображённого виджета
	UPROPERTY()
		class UUserWidget* CurrentWidget;
private:
	//Виджет выбора фигуры
	UPROPERTY()
		TSubclassOf<class UUserWidget> selectedFigureUMG;
	//Виджет главного меню
	UPROPERTY()
		TSubclassOf<class UUserWidget> mainMenuUMG;
};


