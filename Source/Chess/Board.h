// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorFigure.h"
#include "BoardState.h"
#include "FigureInfo.h"
#include "Board.generated.h"
/** 
 * ����� ������� �����
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
	/** ������ ����� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* BoardMesh;
	/** ����� ����� ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* PawnWhite;
	/** ����� ������ ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* PawnBlack;
	/** ����� ����� ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* RockWhite;
	/** ����� ������ ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* RockBlack;
	/** ����� ������ ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KnightWhite;
	/** ����� ������� ���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KnightBlack;
	/** ����� ������ ������� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* BishopWhite;
	/** ����� ������� ������� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* BishopBlack;
	/** ����� ������ ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* QueenWhite;
	/** ����� ������� ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* QueenBlack;
	/** ����� ������ ������ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KingWhite;
	/** ����� ������� ������ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* KingBlack;
	/** ����� ������ ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* ColumnActor;
	/** ����������, ����� �� ����� ������ � ������ ������� ��� ������ ������������� ��������� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 bAIPlayer : 1;
	/** ������ ������� ������ */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 SizeColumn = 236.0f;
	/** 
	* ���������� ������� ���� ��� ���������� ���������� �� �������.
	* @param Pawn - ��������� �� ������
	*/
	UFUNCTION(Server, Reliable)
		void InitializePawn(class AChessPawn* Pawn);
	/**
	 * ������������ ������, �� ������� ����� �������� ������ (����������� ������ �� �������)
	 * @param Moves - ������ �����, ������� ����� ����������
	 */
	UFUNCTION(Client, Reliable)
		void DisplayMoves(const TArray<class UMoveFigure*>& Moves);
	/** ������ ��������� ��������� ����� */
	UFUNCTION(Client, Reliable)
		void HideMoves();
	/**
	 * ���������� ������
	 * @param Figure - ��������� �� ������, ������� ����� ����������
	 */
	UFUNCTION(Server, Reliable)
	void DestroyFigure(class AFigure* Figure);
	/** �������� �����, ��� ����� �������, � ������� ���� ���������� */
	UFUNCTION(Server, Reliable)
		void TogleNextMove();
	/** 
	 * ���������� ��������� �� ������
	 * @param Row - ����� ������
	 * @param Column - ������� ������
	 * @return ��������� �� ������.
	 */
	class AColumn* GetColumn(int32 Row, int32 Column) const;
	/**
	 * ���������� ��������� �� ������
	 * @param Row - �����, � ������� ����������� ������
	 * @param Column - �������, � ������� ����������� ������
	 * @return ��������� �� ������.
	 */
	AFigure* GetFigure(int32 Row, int32 Column) const;
	/**
	 * ���������� ��������� �� ������, ������� ����� ������ ���������
	 * @return ��������� �� ������
	 */
	AChessPawn* GetPlayerPawnNextMove() const;
	/**
	 * ���������� ��������� �� ������, ������� ������ �� ��������� �������
	 * @param ColorFigure - ���� ����� ������
	 * @return ��������� �� ������
	 */
	AChessPawn* GetPlayerPawn(EColorFigure ColorFigure) const;
	/**
	 * ���������� ��� ��������� ���� ���� ����� ������������ �����, ����������� �� �����
	 * @param OutMoves - ������ �� ������, � ������� ����� ��������� ����
	 * @param ColorFigure - ���� �����, ��� ������� ����� �������� ��������� ����.
	 */
	void GetAllMoves(TArray<class UMoveFigure*>& OutMoves, EColorFigure ColorFigure);
	/** ������������� ��������� ������� ��������� ����� */
	void StopSimulation();
	//��������� ���������
	/** ��������� ��������� ������� ��������� ����� */
	void StartSimulation();
	//��������� �������� ��������� ��� ���
	/**
	 * ���������, �������� �� ��������� ������� ��������� �����
	 * @return true ��������� ��������, ����� ������������� ������� ��������� �����
	 * @return false ��������� ���������, ��� ���������� ����, ������ ����� ���������.
	 */
	bool IsSimulated() const;
	/**
	 * ���������� ��� ���� ����� ������������ �����
	 * @param ColorFigure - ���� �����, ��� ������� ����� ��������� ���
	 * @return ������������ ��� ���� �����
	 */
	float GetPowerAllFigures(EColorFigure ColorFigure) const;
	//��������� ������ �������� �������
	/**
	 * ���������� ��������� �� ������
	 * @param ColorFigure - ���� ������
	 * @return ��������� �� ������
	 */
	class AKing* GetKing(EColorFigure ColorFigure) const;
	/**
	 * ���������� ���������� � ������������ � ���������� ����� ������
	 * @param Figure - ������, ���������� � ������� ����� ��������.
	 * @return ��������� � �����������
	 */
	FFigureInfo GetFigureInfo(const class AFigure* Figure) const;
	/**
	 * ��������� ���, ���� ��������� ���������, ��� ���������� ��������� �����, ����� ���������� ����, ���� ��� ��������
	 * @param Move - ��������� ����
	 */
	void MoveFigureOnBoard(class UMoveFigure* Move);
	/** ���������� ��������� ����� (�������� ������ ��� ���������� ���������)*/
	void RollbackBoard();
	//���������� �������� ������ � ������ ������������
	/**
	 * ������� ������ � ��������� � �� �����
	 * @param Figure - ����� ������, ������� ����� ����������
	 * @param Row - �����, � ������� ����� ����������� ������
	 * @param Column - �������, � ������� ����� ����������� ������
	 * @param ColorFigure - ���� ������, ����� ��� ����������� �������� ������
	 */
	void SetFigure(UClass* Figure, int8 Row, int8 Column, EColorFigure ColorFigure);
	/**
	 * �������� ������� ����� � ���, ��� ����� ������� ���������
	 * @param Pawn - ��������� �� ������������ ������
	 */
	void Lose(class AChessPawn* Pawn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	/** ��������� ����� */
	UPROPERTY(Replicated)
		FBoardState BoardState;
	/** ������ ����� */
	UPROPERTY(Replicated)
		TArray<class AColumn*> Columns;
	/** ������ �������� � ���, ����� ������� ����� ������ ��������� */
	UPROPERTY(Replicated)
		EColorFigure NextMove;
	/** ��������� �� ������ ������ */
	UPROPERTY(Replicated)
	AChessPawn* WhitePlayer = nullptr;
	/** ��������� �� ������� ������ */
	UPROPERTY(Replicated)
		AChessPawn* BlackPlayer = nullptr;
	/** ��������� �� ������ ������ */
	UPROPERTY(Replicated)
		class AKing* WhiteKingPointer = nullptr;
	/** ��������� �� ������� ������ */
	UPROPERTY(Replicated)
		class AKing* BlackKingPointer = nullptr;
	/** ����, ����������� �� ��, �������� ��������� ��� ��� */
	uint8 bIsSimulated:1;
	/** ������� ��������� ����� � ��������� */
	FBoardState SimulatedBoardState;
	/** ���������� ��������� ����� � ��������� */
	TArray<FBoardState> SimulatedPrevBoardStates;
	//���������� ������ �� ����� � �������� ������ � � �������� ���������
	/**
	 * ������� ������ � ��������� � �� �����
	 * @param Figure - ����� ������, ������� ����� ����������
	 * @param Row - �����, � ������� ����� ���������� ������
	 * @param Column - �������, � ������� ����� ���������� ������
	 * @param Rotator - ������� ������ ((0.0f, 270, 0.0f) ��� ����� � (0.0f, 90.0f, 0.0f) ��� ������)
	 */
	void SpawnFigure(UClass* Figure, int32 Row, int32 Column, FRotator Rotator);
};
