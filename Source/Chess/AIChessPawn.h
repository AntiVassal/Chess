// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPawn.h"
#include "ColorFigure.h"
#include "AIChessPawn.generated.h"

/**
 * Реализация бота с искуственным интелектом
 */
UCLASS()
class CHESS_API AAIChessPawn : public AChessPawn
{
	GENERATED_BODY()
public:
protected:
	/** 
	 * Когда доска сообщает игроку об ожидании хода, прощитываем лучший
	 * @see AChessPawn::WhaitNextMove
	 */
	void WhaitNextMove_Implementation() override;
	/**
	 * Когда пешка доходит до противоположного конца доски, то ИИ всегда выбирает ферзя
	 * @param Row - Рядок, в котором находилась пешка
	 * @param Column - Столбец, в котором находилась пешка
	 * @see AChessPawn::OnPawnEndPath
	 */
	void OnPawnEndPath_Implementation(int32 Row, int32 Column) override;
	void Win_Implementation() override;
	void Lose_Implementation() override;
private:
	/**
	 * Выполняет поиск лучших ходов
	 * @param Depth - Глубина поиска, чем больше число, тем умнее будет ИИ. ВНИМАНИЕ!!! Этот параметр очень сильно замедляет вычисление хода. Не рекомендутеся указывать число больше 6
	 * @param ColorFigure - Цвет фигур игрока, для которых будет вычислятся лучший ход
	 * @param OutMoves - Указатель на массив, в котором будут сохранены лучшие ходы 
	 * @return Возвращает вес сохранённых ходов. Не имеет смысла сохранять возвращаемое значение, поскольку оно учитывается только при рекурсивном вызове метода.
	 */
	float Minimax(int32 Depth, EColorFigure ColorFigure, TArray<class UMoveFigure*>* OutMoves);
};
