// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessPlayerController.h"
#include "ChessGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
AChessPlayerController::AChessPlayerController()
{
    //Отображаем мышь и включаем возможность клика
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
    //Виджет выбора фигуры
	static ConstructorHelpers::FClassFinder <UUserWidget>
        selectFigure(TEXT("WidgetBlueprint'/Game/UMG/SelectFigure.SelectFigure_C'"));
	this->selectedFigureUMG = selectFigure.Class;
    //Виджет выиграша
	static ConstructorHelpers::FClassFinder <UUserWidget> win(TEXT("WidgetBlueprint'/Game/UMG/YurWin.YurWin_C'"));
    this->winUMG = win.Class;
    //Виджет проиграша
	static ConstructorHelpers::FClassFinder <UUserWidget> lose(TEXT("WidgetBlueprint'/Game/UMG/YourLose.YourLose_C'"));
    this->loseUMG = lose.Class;
    //Виджет главного меню
    static ConstructorHelpers::FClassFinder <UUserWidget> mainMenu(TEXT("WidgetBlueprint'/Game/UMG/MainMenu.MainMenu_C'"));
    this->mainMenuUMG = mainMenu.Class;

}
void AChessPlayerController::BeginPlay() {
	this->SetInputMode(FInputModeGameAndUI());
    //При старте игры отобразить главное меню
    ChangeMenuWidget(this->mainMenuUMG);
}
void AChessPlayerController::selectFigureTo_Implementation(int32 row, int32 column) {
	this->_row = row;
	this->_column = column;
    //Отобразить меню выбора фигуры
	this->ChangeMenuWidget(this->selectedFigureUMG);
}
void AChessPlayerController::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    //Сначала прячем предыдущий виджет
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    //Отображаем новый виджет
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}