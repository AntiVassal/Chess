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
	//������ �����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* boardMesh;
	//����� ����� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* pawnWhite;
	//����� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* pawnBlack;
	//����� ����� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* rockWhite;
	//����� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* rockBlack;
	//����� ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* knightWhite;
	//����� ������� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* knightBlack;
	//����� ������ �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* bishopWhite;
	//����� ������� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* bishopBlack;
	//����� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* queenWhite;
	//����� ������� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* queenBlack;
	//����� ������ ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* kingWhite;
	//����� ������� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* kingBlack;
	//����� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* columnActor;
	//����������, ����� �� ����� ������ � ������ ������� ��� ������ ������������� ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 bIsAIPlayer : 1;
	//���������� ��� ���������� ���������� �� ����� � ������
	//���������� ������ �� �������
	UFUNCTION(Server, Reliable)
		void initializePawn(class AChessPawn* pawn);
	//������������ ���������� ����
	UFUNCTION(Client, Reliable)
		void displayMoves(const TArray<class UMoveFigure*>& moves);
	//������ ��������� ��������� �����
	UFUNCTION(Client, Reliable)
		void hideMoves();
	//���������� ������
	UFUNCTION(Server, Reliable)
	void destroyFigure(class AFigure* figure);
	//���������, ��� ����� ������� � ���, ���� ������� ���������
	UFUNCTION(Server, Reliable)
		void togleNextMove();

	//�������� ������ �� �����
	class AColumn* getColumn(int32 row, int32 column) const;
	//�������� ������ �� �����
	AFigure* getFigure(int32 row, int32 column) const;
	//�������� ������, ������� ����� ������ ���������
	AChessPawn* getNextMovePawn() const;
	//�������� ������, ������� ������ �� ��������� �������
	AChessPawn* getPawn(DirectionFigure figure) const;
	//�������� ��� ��������� ����
	void getAllMoves(TArray<class UMoveFigure*>& outMoves, DirectionFigure direct);
	//���������� ���������
	void stopSimulation();
	//��������� ���������
	void startSimulation();
	//��������� �������� ��������� ��� ���
	bool isSimulated() const;
	//�������� ��� ���� �����
	float getPower(DirectionFigure direct) const;
	//��������� ������ �������� �������
	class AKing* getKing(DirectionFigure direct) const;
	//�������� �����, � ������� ����������� ������
	int32 getRow(const class AFigure* figure) const;
	//�������� �������, � ������� ����������� ������
	int32 getColumn(const class AFigure* figure) const;
	//��������� ���
	void moveFigure(class UMoveFigure* move);
	//�������� ��������� ����� (�������� ������ ��� ���������� ���������)
	void rollback();
	//�������� ���������� ������������ ����� �������� ������
	int32 getCountMoves(const class AFigure* figure) const;
	//���������� �������� ������ � ������ ������������
	void setFigure(UClass* figure, int8 row, int8 column, DirectionFigure direct);
	//�������� ������� ������ � ���, ��� �������� ����� ��������
	void lose(class AChessPawn* pawn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	//��������� �����
	UPROPERTY(Replicated)
		FBoardData board;
	//������ �����
	UPROPERTY(Replicated)
		TArray<class AColumn*> columns;
	//��� ����� ������
	UPROPERTY(Replicated)
		TEnumAsByte<DirectionFigure> nextMove;
	//��������� �� ������ ������
	UPROPERTY(Replicated)
	AChessPawn* white = nullptr;
	//��������� �� ������� ������
	UPROPERTY(Replicated)
		AChessPawn* black = nullptr;
	//��������� �� ������ ������
	UPROPERTY(Replicated)
		class AKing* whiteKing = nullptr;
	//��������� �� ������� ������
	UPROPERTY(Replicated)
		class AKing* blackKing = nullptr;
	//����, ����������� �� ��, �������� ��������� ��� ���
		uint8 _isSimulated:1;
		//������� ��������� ����� � ���������
		FBoardData simulatedBoard;
		//���������� ��������� ����� � ���������
		TArray<FBoardData> simulatedPrevBoards;
		//���������� ������ �� ����� � �������� ������ � � �������� ���������
	void spawnFigure(UClass* figure, int32 row, int32 column, FRotator rotator);
};
