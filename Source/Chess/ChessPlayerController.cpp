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
        SelectFigureWidget(TEXT("WidgetBlueprint'/Game/UMG/SelectFigure.SelectFigure_C'"));
	this->SelectedFigureUMG = SelectFigureWidget.Class;
    //������ ��������
	static ConstructorHelpers::FClassFinder <UUserWidget> WinWidget(TEXT("WidgetBlueprint'/Game/UMG/YurWin.YurWin_C'"));
    this->WinUMG = WinWidget.Class;
    //������ ���������
	static ConstructorHelpers::FClassFinder <UUserWidget> LoseWidget(TEXT("WidgetBlueprint'/Game/UMG/YourLose.YourLose_C'"));
    this->LoseUMG = LoseWidget.Class;
    //������ �������� ����
    static ConstructorHelpers::FClassFinder <UUserWidget> MainMenuWidget(TEXT("WidgetBlueprint'/Game/UMG/MainMenu.MainMenu_C'"));
    this->MainMenuUMG = MainMenuWidget.Class;

}
void AChessPlayerController::BeginPlay() {
	this->SetInputMode(FInputModeGameAndUI());
    //��� ������ ���� ���������� ������� ����
    ChangeMenuWidget(this->MainMenuUMG);
}
void AChessPlayerController::SelectFigureTo_Implementation(int32 Row, int32 Column) {
	this->RowPawnFigure = Row;
	this->ColumnPawnFigure = Column;
    //���������� ���� ������ ������
	this->ChangeMenuWidget(this->SelectedFigureUMG);
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