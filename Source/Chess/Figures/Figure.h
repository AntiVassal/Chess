// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../ColorFigure.h"
#include "Figure.generated.h"
/** Класс, описывающий каждую фигуру */
UCLASS()
class CHESS_API AFigure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigure();

protected:
	/** Модель фигуры */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* FigureMesh;
	/** Цвет фигуры (чёрный или белый) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EColorFigure Color;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	 * Метод регистрирует возможные ходы
	 * @param Move - экземпляр хода 
	 */
	void RegisterMove(class UMoveFigure* Move);
private:
	/** Сохранённый указатель на доску. Нужен для корректной работы игровой логики */
	UPROPERTY(Replicated)
	class ABoard* BoardActor;
	/** Массив всех зарегистрированых ходов */
	UPROPERTY()
	TArray<class UMoveFigure*> Moves;
	/** Хранится местоположение, куда нужно переместить фигуру во время хода (Нужно для работы анимации перемещения) */
	FVector TargetMoveAnimation;
	/** Хранится местоположение фигуры до начала перемещения (Нужно для работы анимации перемещения) */
	FVector SourceMoveAnimation;
	/** Время воспроизведения анимации (0 - анимация ещё не началась, 1 - анимация закончилась) */
	float TimeAnimationExecuted;
	/** Если true - значит анимация завершена и можно сообщать игре, что ход закончен */
	bool bEndMove;
	/** Указатель на последний ход. Нужен для того, чтобы сообщить игре о том, что он завершён. */
	class UMoveFigure* LastMove;
public:
	/**
	 * Функция возпроизводит анимацию перемещения
	 * @param Move - Экземпляр хода, описывающий перемещение
	 */
	UFUNCTION(Server, reliable)
	virtual void AnimateMove(class UMoveFigure* Move);
	/**
	 * Сохраняет указатель на доску, в приватное поле.
	 * @param Board - Указатель на доску
	 * @warning - Вызывается из класса доски во время спауна. В других случаях вызывать не нужно. 
	 */
	UFUNCTION(Server, reliable)
	void Initialize(ABoard* Board);
	/** Скорость перемещения в секундах */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedMoveFigure = 1.0f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/**
	 * Получает все ходы фигуры, которые соответствуют правилам.
	 * @param OutMoves - Ссылка на массив, в который будут записаны ходы
	 */
	virtual void GetMoves(TArray<class UMoveFigure*>& OutMoves);
	/**
	 * Получает цвет фигуры
	 * @return Элемент перечисления, который обозначает цвет фигуры. (EColorFigure::WHITE - для белых и EColorFigure::BLACK - для чёрных)
	 */
	EColorFigure GetColor() const;
	/**
	 * Получить указатель на игровую доску
	 * @return Указатель на игровую доску
	 */
	class ABoard* GetBoard() const;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	/**
	 * Получает силу фигуры, в зависимости от расположения на игровой доске
	 * @param Row - рядок, в котором расположена фигура
	 * @param Column - столбец, в котором расположена фигура
	 * @return Сила фигуры
	 */
	virtual float GetPower(int8 Row, int8 Column) const;
};
