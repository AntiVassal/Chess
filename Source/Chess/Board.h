// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DirectionFigure.h"
#include "FBoard.h"
#include "Board.generated.h"

UCLASS()
class CHESS_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Модель доски
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* boardMesh;
	//Класс белой пешки
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* pawnWhite;
	//Класс чёрной пешки
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* pawnBlack;
	//Класс белой башни
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* rockWhite;
	//Класс чёрной башни
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* rockBlack;
	//Класс белого коня
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* knightWhite;
	//Класс чёрного коня
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* knightBlack;
	//Класс белого офицера
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* bishopWhite;
	//Класс чёрного офицера
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* bishopBlack;
	//Класс белого ферзя
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* queenWhite;
	//Класс чёрного ферзя
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* queenBlack;
	//Класс белого короля
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* kingWhite;
	//Класс чёрного короля
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* kingBlack;
	//Класс ячейки доски
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* columnActor;
	//Определяет, будет ли игрок играть с другим игроком или против искуственного интелекта
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 bIsAIPlayer : 1;
	//Вызывается для сохранения указателей на доску и игрока
	//Вызывается только на сервере
	UFUNCTION(Server, Reliable)
		void initializePawn(class AChessPawn* pawn);
	//Подсвечивает переданные ходы
	UFUNCTION(Client, Reliable)
		void displayMoves(const TArray<class UMoveFigure*>& moves);
	//Прячет подсветку возможных ходов
	UFUNCTION(Client, Reliable)
		void hideMoves();
	//Уничтожает фигуру
	UFUNCTION(Server, Reliable)
	void destroyFigure(class AFigure* figure);
	//Указывает, что игрок походил и ждёт, пока походит противник
	UFUNCTION(Server, Reliable)
		void togleNextMove();

	//Получить клетку на доске
	class AColumn* getColumn(int32 row, int32 column) const;
	//Получить фигуру на доске
	AFigure* getFigure(int32 row, int32 column) const;
	//Получить игрока, который будет ходить следующим
	AChessPawn* getNextMovePawn() const;
	//Получить игрока, который играет за указанную сторону
	AChessPawn* getPawn(DirectionFigure figure) const;
	//Получить все возможные ходы
	void getAllMoves(TArray<class UMoveFigure*>& outMoves, DirectionFigure direct);
	//Остановить симуляцию
	void stopSimulation();
	//Запустить симуляцию
	void startSimulation();
	//Проверить включена симуляция или нет
	bool isSimulated() const;
	//Получить вес всех фигур
	float getPower(DirectionFigure direct) const;
	//Получение короля указаной стороны
	class AKing* getKing(DirectionFigure direct) const;
	//Получить рядок, в котором расположена фигура
	int32 getRow(const class AFigure* figure) const;
	//Получить столбец, в котором расположена фигура
	int32 getColumn(const class AFigure* figure) const;
	//Выполнить ход
	void moveFigure(class UMoveFigure* move);
	//Откатить состояние доски (возможно только при включённой симуляции)
	void rollback();
	//Получить количество произведённых ходов указаной фигуры
	int32 getCountMoves(const class AFigure* figure) const;
	//Установить указаную фигуру в нужном расположении
	void setFigure(UClass* figure, int8 row, int8 column, DirectionFigure direct);
	//Сообщает другому игроку о том, что указаный игрок проиграл
	void lose(class AChessPawn* pawn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	//Состояние доски
	UPROPERTY(Replicated)
		FBoardData board;
	//Клетки доски
	UPROPERTY(Replicated)
		TArray<class AColumn*> columns;
	//Кто будет ходить
	UPROPERTY(Replicated)
		TEnumAsByte<DirectionFigure> nextMove;
	//Указатель на белого игрока
	UPROPERTY(Replicated)
	AChessPawn* white = nullptr;
	//Указатель на чёрного игрока
	UPROPERTY(Replicated)
		AChessPawn* black = nullptr;
	//Указатель на белого короля
	UPROPERTY(Replicated)
		class AKing* whiteKing = nullptr;
	//Указатель на чёрного короля
	UPROPERTY(Replicated)
		class AKing* blackKing = nullptr;
	//Флаг, указывающий на то, включена симуляция или нет
		uint8 _isSimulated:1;
		//Текущее состояние доски в симуляции
		FBoardData simulatedBoard;
		//Предыдущие состояния доски в симуляции
		TArray<FBoardData> simulatedPrevBoards;
		//Разместить фигуру на доске в указаной клетке и с указаным поворотом
	void spawnFigure(UClass* figure, int32 row, int32 column, FRotator rotator);
};
