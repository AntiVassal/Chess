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
	//������ ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* figure;
	//���� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TEnumAsByte<DirectionFigure> direction;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//����������� ���������� ����
	void addMove(class UMoveFigure* move);
private:
	//��������� �� �����
	UPROPERTY(Replicated)
		class ABoard* board;
	//��������� ����
	UPROPERTY()
	TArray<class UMoveFigure*> moves;
	//���� ���������� ������ �� ����� ��������
	FVector target;
	//������ ���������� ������ �� ����� ��������
	FVector source;
	//����� �����������, ������� �������� ��� �����������
	float time;
	//��������� �� �������� ���������� ����
	bool isEndMove;
	//��������� ���
	class UMoveFigure* currentMove;
public:
	//����������� ������
	UFUNCTION(Server, reliable)
		virtual void moveTo(class UMoveFigure* move);
	//���������� ����������
	UFUNCTION(Server, reliable)
	void initialize(ABoard* aBoard);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//��������� ���� ��������� �����
	virtual void getMoves(TArray<class UMoveFigure*>& outMoves);
	//��������� ����� ������
	DirectionFigure getDirection() const;
	//��������� �����
	class ABoard* getBoard() const;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//��������� ���� ������
	virtual float getPower(int8 row, int8 column) const;
};
