// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessPlayerController.h"
#include "ChessGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
AChessPlayerController::AChessPlayerController()
{
    //���������� ���� � �������� ����������� �����
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
    //������ ������ ������
	static ConstructorHelpers::FClassFinder <UUserWidget>
        selectFigure(TEXT("WidgetBlueprint'/Game/UMG/SelectFigure.SelectFigure_C'"));
	this->selectedFigureUMG = selectFigure.Class;
    //������ ��������
	static ConstructorHelpers::FClassFinder <UUserWidget> win(TEXT("WidgetBlueprint'/Game/UMG/YurWin.YurWin_C'"));
    this->winUMG = win.Class;
    //������ ���������
	static ConstructorHelpers::FClassFinder <UUserWidget> lose(TEXT("WidgetBlueprint'/Game/UMG/YourLose.YourLose_C'"));
    this->loseUMG = lose.Class;
    //������ �������� ����
    static ConstructorHelpers::FClassFinder <UUserWidget> mainMenu(TEXT("WidgetBlueprint'/Game/UMG/MainMenu.MainMenu_C'"));
    this->mainMenuUMG = mainMenu.Class;

}
void AChessPlayerController::BeginPlay() {
	this->SetInputMode(FInputModeGameAndUI());
    //��� ������ ���� ���������� ������� ����
    ChangeMenuWidget(this->mainMenuUMG);
}
void AChessPlayerController::selectFigureTo_Implementation(int32 row, int32 column) {
	this->_row = row;
	this->_column = column;
    //���������� ���� ������ ������
	this->ChangeMenuWidget(this->selectedFigureUMG);
}
void AChessPlayerController::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    //������� ������ ���������� ������
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    //���������� ����� ������
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}