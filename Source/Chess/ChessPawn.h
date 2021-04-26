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
	//Цвет фигур, за которые играет игрок
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing=onDirectionReplicated)
	TEnumAsByte<DirectionFigure> direction;
	//Функция вызвывается каждый раз, когда переменная direction реплицируется
	UFUNCTION()
	void onDirectionReplicated();
	//Отображает сообщение о выиграше
	UFUNCTION(Client, reliable)
		void win();
	//Отображатет сообщение о проигрыше
	UFUNCTION(Client, reliable)
		void lose();
	//Сообщает, что одна из пешек добралась до противоположного конца доски и заменяет её на одну из возможных фигур
	UFUNCTION(Server, reliable)
		void pawnEndPath(int32 row, int32 column);
	//Ожидание хода
	UFUNCTION(Server, reliable)
		void whaitMove();
	//Размещение одной из фигур в зависимости од того, за какой цвет играет игрок
	UFUNCTION(BlueprintCallable)
		void selectedFigureSwap(TSubclassOf<AFigure> whiteFigure, TSubclassOf<AFigure> blackFigure, int32 row, int32 column);
protected:
	virtual void BeginPlay() override;
	//Событие клика
	void TriggerClick();
	//Трасировка луча
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* camera;
	//Модель доски
	UPROPERTY(Replicated)
		class ABoard* board;
private:
	//Клик по доске или фигуре
	UFUNCTION(Server, reliable)
		void clickToBoard(FHitResult HitResult);
	//Разместить фигуру в указаную клетку
	UFUNCTION(Server, reliable)
		void swapPawnToFigure(TSubclassOf<AFigure> figure, int32 row, int32 column);
	//Клик по доске или фигуре (отображение доступных ходов)
	UFUNCTION(Client, reliable)
		void clickToBoardClient(FHitResult HitResult);
	//Выбранная фигура
	class AFigure* selectedFigure;
};
