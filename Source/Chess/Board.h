// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorFigure.h"
#include "BoardState.h"
#include "FigureInfo.h"
#include "Board.generated.h"
/** 
 * Класс игровой доски
 */
UCLASS()
class CHESS_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Модель доски */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* BoardMesh;
	/** Класс белой пешки */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* PawnWhite;
	/** Класс чёрной пешки */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* PawnBlack;
	/** Класс белой башни */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* RockWhite;
	/** Класс чёрной башни */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* RockBlack;
	/** Класс белого коня */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KnightWhite;
	/** Класс чёрного коня */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KnightBlack;
	/** Класс белого офицера */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* BishopWhite;
	/** Класс чёрного офицера */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* BishopBlack;
	/** Класс белого ферзя */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* QueenWhite;
	/** Класс чёрного ферзя */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* QueenBlack;
	/** Класс белого короля */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KingWhite;
	/** Класс чёрного короля */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KingBlack;
	/** Класс ячейки доски */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* ColumnActor;
	/** Определяет, будет ли игрок играть с другим игроком или против искуственного интелекта */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 bAIPlayer : 1;
	/** Размер игровой клетки */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 SizeColumn = 236.0f;
	/** 
	* Вызывается вначале игры для сохранения указателей на игроков.
	* @param Pawn - Указатель на игрока
	*/
	UFUNCTION(Server, Reliable)
		void InitializePawn(class AChessPawn* Pawn);
	/**
	 * Подсвечивает клетки, на которые может походить фигура (Выполняется только на клиенте)
	 * @param Moves - Массив ходов, которые нужно подсветить
	 */
	UFUNCTION(Client, Reliable)
		void DisplayMoves(const TArray<class UMoveFigure*>& Moves);
	/** Прячет подсветку возможных ходов */
	UFUNCTION(Client, Reliable)
		void HideMoves();
	/**
	 * Уничтожает фигуру
	 * @param Figure - Указатель на фигуру, которую нужно уничтожить
	 */
	UFUNCTION(Server, Reliable)
	void DestroyFigure(class AFigure* Figure);
	/** Сообщает доске, что игрок походил, и ожидает хода противника */
	UFUNCTION(Server, Reliable)
		void TogleNextMove();
	/** 
	 * Возвращает указатель на клетку
	 * @param Row - рядок клетки
	 * @param Column - столбец клетки
	 * @return Указатель на клетку.
	 */
	class AColumn* GetColumn(int32 Row, int32 Column) const;
	/**
	 * Возвращает указатель на фигуру
	 * @param Row - рядок, в котором расположена фигура
	 * @param Column - столбец, в котором расположена фигура
	 * @return Указатель на фигуру.
	 */
	AFigure* GetFigure(int32 Row, int32 Column) const;
	/**
	 * Возвращает указатель на игрока, который будет ходить следующим
	 * @return Указатель на игрока
	 */
	AChessPawn* GetPlayerPawnNextMove() const;
	/**
	 * Возвращает указатель на игрока, который играет за указанную сторону
	 * @param ColorFigure - Цвет фигур игрока
	 * @return Указатель на игрока
	 */
	AChessPawn* GetPlayerPawn(EColorFigure ColorFigure) const;
	/**
	 * Возвращает все возможные ходы всех фигур определённого цвета, находящихся на доске
	 * @param OutMoves - Ссылка на массив, в котором будут сохранены ходы
	 * @param ColorFigure - Цвет фигур, для которых нужно получить возможные ходы.
	 */
	void GetAllMoves(TArray<class UMoveFigure*>& OutMoves, EColorFigure ColorFigure);
	/** Останавливает симуляцию будущих состояний доски */
	void StopSimulation();
	//Запустить симуляцию
	/** Запускает симуляцию будущих состояний доски */
	void StartSimulation();
	//Проверить включена симуляция или нет
	/**
	 * Проверяет, включена ли симуляция будущих состояний доски
	 * @return true Симуляция включена, можно предсказывать будущие состояния доски
	 * @return false Симуляция отключена, при выполнении хода, фигуры будут двигаться.
	 */
	bool IsSimulated() const;
	/**
	 * Возвращает вес всех фигур определённого цвета
	 * @param ColorFigure - Цвет фигур, для которых нужно посчитать вес
	 * @return Суммированый вес всех фигур
	 */
	float GetPowerAllFigures(EColorFigure ColorFigure) const;
	//Получение короля указаной стороны
	/**
	 * Возвращает указатель на короля
	 * @param ColorFigure - Цвет короля
	 * @return Указатель на короля
	 */
	class AKing* GetKing(EColorFigure ColorFigure) const;
	/**
	 * Возвращает информацию о расположении и количестве ходов фигуры
	 * @param Figure - Фигура, информацию о которой нужно получить.
	 * @return Структура с информацией
	 */
	FFigureInfo GetFigureInfo(const class AFigure* Figure) const;
	/**
	 * Выполняет ход, если симуляция отключена, или симулирует состояние доски, после выполнения хода, если она включена
	 * @param Move - Экземпляр хода
	 */
	void MoveFigureOnBoard(class UMoveFigure* Move);
	/** Откатывает состояние доски (возможно только при включённой симуляции)*/
	void RollbackBoard();
	//Установить указаную фигуру в нужном расположении
	/**
	 * Спавнит фигуру и размещает её на доске
	 * @param Figure - Класс фигуры, которую нужно заспавнить
	 * @param Row - Рядок, в котором будет расположена фигура
	 * @param Column - Столбец, в котором будет расположена фигура
	 * @param ColorFigure - Цвет фигуры, нужен для правильного поворота фигуры
	 */
	void SetFigure(UClass* Figure, int8 Row, int8 Column, EColorFigure ColorFigure);
	/**
	 * Сообщает игровой доске о том, что игрок признал поражение
	 * @param Pawn - Указатель на проигравшего игрока
	 */
	void Lose(class AChessPawn* Pawn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	/** Состояние доски */
	UPROPERTY(Replicated)
		FBoardState BoardState;
	/** Клетки доски */
	UPROPERTY(Replicated)
		TArray<class AColumn*> Columns;
	/** Хранит значение о том, какая сторона будет ходить следующей */
	UPROPERTY(Replicated)
		EColorFigure NextMove;
	/** Указатель на белого игрока */
	UPROPERTY(Replicated)
	AChessPawn* WhitePlayer = nullptr;
	/** Указатель на чёрного игрока */
	UPROPERTY(Replicated)
		AChessPawn* BlackPlayer = nullptr;
	/** Указатель на белого короля */
	UPROPERTY(Replicated)
		class AKing* WhiteKingPointer = nullptr;
	/** Указатель на чёрного короля */
	UPROPERTY(Replicated)
		class AKing* BlackKingPointer = nullptr;
	/** Флаг, указывающий на то, включена симуляция или нет */
	uint8 bIsSimulated:1;
	/** Текущее состояние доски в симуляции */
	FBoardState SimulatedBoardState;
	/** Предыдущие состояния доски в симуляции */
	TArray<FBoardState> SimulatedPrevBoardStates;
	//Разместить фигуру на доске в указаной клетке и с указаным поворотом
	/**
	 * Спавнит фигуру и размещает её на доске
	 * @param Figure - Класс фигуры, которую нужно заспавнить
	 * @param Row - Рядок, в котором нужно заспавнить фигуру
	 * @param Column - Столбец, в котором нужно заспавнить фигуру
	 * @param Rotator - Поворот фигуры ((0.0f, 270, 0.0f) для белых и (0.0f, 90.0f, 0.0f) для чёрных)
	 */
	void SpawnFigure(UClass* Figure, int32 Row, int32 Column, FRotator Rotator);
};
