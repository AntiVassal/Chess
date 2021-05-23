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
        SelectFigureWidget(TEXT("WidgetBlueprint'/Game/UMG/SelectFigure.SelectFigure_C'"));
	this->SelectedFigureUMG = SelectFigureWidget.Class;
    //Виджет выиграша
	static ConstructorHelpers::FClassFinder <UUserWidget> WinWidget(TEXT("WidgetBlueprint'/Game/UMG/YurWin.YurWin_C'"));
    this->WinUMG = WinWidget.Class;
    //Виджет проиграша
	static ConstructorHelpers::FClassFinder <UUserWidget> LoseWidget(TEXT("WidgetBlueprint'/Game/UMG/YourLose.YourLose_C'"));
    this->LoseUMG = LoseWidget.Class;
    //Виджет главного меню
    static ConstructorHelpers::FClassFinder <UUserWidget> MainMenuWidget(TEXT("WidgetBlueprint'/Game/UMG/MainMenu.MainMenu_C'"));
    this->MainMenuUMG = MainMenuWidget.Class;

}
void AChessPlayerController::BeginPlay() {
	this->SetInputMode(FInputModeGameAndUI());
    //При старте игры отобразить главное меню
    ChangeMenuWidget(this->MainMenuUMG);
}
void AChessPlayerController::SelectFigureTo_Implementation(int32 Row, int32 Column) {
	this->RowPawnFigure = Row;
	this->ColumnPawnFigure = Column;
    //Отобразить меню выбора фигуры
	this->ChangeMenuWidget(this->SelectedFigureUMG);
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