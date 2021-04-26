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
	//��������, �������� �� ��� ��� ���
	virtual bool isMoving();
	//���������� ����
	virtual void move();
	//����� ���� � ���������
	virtual void rollback();
	//�������� ������� ����������
	virtual int8 toColumn() const;
	//�������� ����� ����������
	virtual int8 toRow() const;
	//�������� ������, ������� ����� ����������
	virtual class AFigure* getDestroyFigure() const;
	//�������� � ���, ��� ��� ��������
	virtual void finishMove();
	//������� ����� � �������
	int8 getRow() const;
	//������� ������� � �������
	int8 getColumn() const;
	//������
	class AFigure* getFigure() const;
	//���������� ��������� ������
	void initialzie(class AFigure* figure);
private:
	//������
	class AFigure* _figure;
};
