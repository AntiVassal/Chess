// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ColorFigure.h"
#include "Figures/Figure.h"
#include "ChessPawn.generated.h"

UCLASS(config=Game)
class AChessPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	/** Цвет фигур, за которые играет игрок */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing= OnDirectionReplicated)
	EColorFigure ColorSide;
	/** Вызывается, при инициализации игрока и определении того, за какую из сторон он будет играть */
	UFUNCTION()
	void OnDirectionReplicated();
	/** Сообщает игроку, что он выиграл */
	UFUNCTION(Client, reliable)
		void Win();
	/** Сообщает игроку, что он проиграл */
	UFUNCTION(Client, reliable)
		void Lose();
	/** Сообщает, что одна из пешек добралась до противоположного конца доски, чтобы заменить её на одну из возможных фигур */
	UFUNCTION(Server, reliable)
		void OnPawnEndPath(int32 Row, int32 Column);
	/** Сообщает игроку, что теперь его ход */
	UFUNCTION(Server, reliable)
		void WhaitNextMove();
	/**
	 * Размещает одну из выбраных фигур на доске, в зависимости от цвета игрока
	 * @param WhiteFigure - Выбраная фигура для белого цвета
	 * @param BlackFigure - Выбраная фигура для чёрного цвета
	 * @param Row - Рядок, в котором будет размещена фигура
	 * @param Column - Столбец, в котором будет размещена фигура
	 */
	UFUNCTION(BlueprintCallable)
		void SelectedFigureSwap(TSubclassOf<AFigure> WhiteFigure, TSubclassOf<AFigure> BlackFigure, int32 Row, int32 Column);
protected:
	virtual void BeginPlay() override;
	/** Сообщает о том, что игрок кликнул по доске */
	void TriggerClick();
	/**
	 * Трасировка луча, для определения того, куда именно кликнул игрок
	 * @param Start - Начало луча
	 * @param End - Конец луча
	 * @param bDrawDebugHelpers - Определяет, нужно ли рисвать луч или нет.
	 */
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	/** Камера, через которую игрок будет видеть игровую доску */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* CameraComponent;
	/** Указатель на игровую доску */
	UPROPERTY(Replicated)
		class ABoard* BoardActor;
private:
	/**
	 * Вызывается, когда лучь трасировки пересекается с доской или фигурой. Сервер либо сохраняет выбранную фигуру, либо перемещает выбраную фигуру в указаное местоположение
	 * @param HitResult - Информация о месте, куда кликнул игрок
	 */
	UFUNCTION(Server, reliable)
		void OnClickToBoard(FHitResult HitResult);
	/**
	 * Спавнит и размещает фигуру на игровой доске
	 * @param Figure - Класс фигуры, которую нужно разместить на доске
	 * @param Row - Рядок, в котором фигура будет размещена
	 * @param Column - Столбец, в котором фигура будет размещена
	 */
	UFUNCTION(Server, reliable)
		void SwapPawnToFigure(TSubclassOf<AFigure> Figure, int32 Row, int32 Column);
	/**
	 * Вызывается, когда лучь трасировки пересекается с фигурой и подсвечивает все возможные ходы выбраной фигуры
	 * @param HitResult - Информация о месте, куда кликнул игрок
	 */
	UFUNCTION(Client, reliable)
		void OnClickToBoardClient(FHitResult HitResult);
	/** Указатель на фигуру, которая будет ходить */
	class AFigure* SelectedFigure;
};
