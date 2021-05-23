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
	 * Отображает меню, с выбором фигуры, которая будет размещена вместо пешки
	 * @param Row - Рядок, в котором находилась пешка, дошедшая до конца доски
	 * @param Column - Столбец, в котором находилась пешка, дошедшая до конца доски
	 */
	UFUNCTION(Client, reliable)
	void SelectFigureTo(int32 Row, int32 Column);
	/**
	 * Заменяет показаный виджет на тот, который мы передали
	 * @param NewWidgetClass - Виджет, который нужно отобразить
	 */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<class UUserWidget> NewWidgetClass);
	/** Виджет выиграша */
	UPROPERTY()
		TSubclassOf<class UUserWidget> WinUMG;
	/** Виджет проигрыша */
	UPROPERTY()
		TSubclassOf<class UUserWidget> LoseUMG;
protected:
	/** Рядок пешки, которая дошла до конца доски */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 RowPawnFigure;
	/** Столбец пешки, которая дошла до конца доски */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ColumnPawnFigure;
	/** Указатель на виджет, который сейчас отображатеся на экране */
	UPROPERTY()
		class UUserWidget* CurrentWidget;
private:
	/** Виджет выбора фигуры, на смену пешки */
	UPROPERTY()
		TSubclassOf<class UUserWidget> SelectedFigureUMG;
	/** Виджет главного меню */
	UPROPERTY()
		TSubclassOf<class UUserWidget> MainMenuUMG;
};


