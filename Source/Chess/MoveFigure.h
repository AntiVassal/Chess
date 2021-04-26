// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MoveFigure.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UMoveFigure : public UObject
{
	GENERATED_BODY()
public:
	//Проверка, возможен ли ход или нет
	virtual bool isMoving();
	//Выполнение хода
	virtual void move();
	//Откат хода в симуляции
	virtual void rollback();
	//Получает столбец назначения
	virtual int8 toColumn() const;
	//Получает рядок назначения
	virtual int8 toRow() const;
	//Получает фигуру, которая будет уничтожена
	virtual class AFigure* getDestroyFigure() const;
	//Сообщает о том, что ход завершён
	virtual void finishMove();
	//Текущий рядок с фигурой
	int8 getRow() const;
	//Текущий столбец с фигурой
	int8 getColumn() const;
	//Фигура
	class AFigure* getFigure() const;
	//Сохранение указателя фигуры
	void initialzie(class AFigure* figure);
private:
	//Фигура
	class AFigure* _figure;
};
