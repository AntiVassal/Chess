// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionFigure.h"
#include "Figure.generated.h"

UCLASS()
class CHESS_API AFigure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigure();

protected:
	//Модель фигуры
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* figure;
	//Цвет фигуры
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TEnumAsByte<DirectionFigure> direction;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Регистрация возможного хода
	void addMove(class UMoveFigure* move);
private:
	//Указатель на доску
	UPROPERTY(Replicated)
		class ABoard* board;
	//Возможные ходы
	UPROPERTY()
	TArray<class UMoveFigure*> moves;
	//Куда перемещать фигуру во время анимации
	FVector target;
	//Откуда перемещать фигуру во время анимации
	FVector source;
	//Время указывающее, сколько анимация уже выполняется
	float time;
	//Указывает на успешное завершение хода
	bool isEndMove;
	//Последний ход
	class UMoveFigure* currentMove;
public:
	//Переместить фигуру
	UFUNCTION(Server, reliable)
		virtual void moveTo(class UMoveFigure* move);
	//Сохранение указателей
	UFUNCTION(Server, reliable)
	void initialize(ABoard* aBoard);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Получение всех возможных ходов
	virtual void getMoves(TArray<class UMoveFigure*>& outMoves);
	//Получение цвета фигуры
	DirectionFigure getDirection() const;
	//Получение доски
	class ABoard* getBoard() const;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//Получение веса фигуры
	virtual float getPower(int8 row, int8 column) const;
};
