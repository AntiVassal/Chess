// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Figures/Figure.h"
#include "Board.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Column.h"
#include "Figures/King.h"
#include "Moves/MoveFigure.h"
#include "ChessPlayerController.h"
#include "ChessGameMode.h"
AChessPawn::AChessPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	this->CameraComponent = this->CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->SetRootComponent(this->CameraComponent);
	this->bReplicates = true;
}

void AChessPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AChessPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//���� �� �����
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AChessPawn::TriggerClick);
}
void AChessPawn::TriggerClick()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		//���������� ����
		this->TraceForBlock(Start, End, true);
	}
}

void AChessPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		//���� ���� ���������� � ������ ��� �������, �� ��������� ����������� ��������
		this->OnClickToBoard(HitResult);
		this->OnClickToBoardClient(HitResult);
	}
}
void AChessPawn::OnClickToBoard_Implementation(FHitResult HitResult) {
	//���� ��� �� ���, �� ������ �� ������
	if (this->BoardActor != nullptr && this->BoardActor->GetPlayerPawnNextMove() == this) {
		AFigure* Figure = Cast<AFigure>(HitResult.Actor.Get());
		if (Figure != nullptr) {
			if (this->SelectedFigure == nullptr || this->ColorSide == Figure->GetColor()) {
				//���� �������� �� ������, � ��� ���� ��� ����, �� �������� � ��� ����
				this->SelectedFigure = Figure;
			} else {
				//���� �� �������� �� ������ ����������, �� �������� ��� ��������� ���� �������� ������
				TArray<UMoveFigure*> Moves;
				this->SelectedFigure->GetMoves(Moves);
				FFigureInfo FigureInfo = this->BoardActor->GetFigureInfo(Figure);
				for (UMoveFigure* Move : Moves) {
					FFigureInfo MoveFigureInfo = Move->GetFigureInfoAfterMoving();
					if (MoveFigureInfo.Row == FigureInfo.Row && 
						MoveFigureInfo.Column == FigureInfo.Column) {
						//���� ���� �� ����� ������ � ������������� ������ ����������, �� ���� �
						Move->Move();;
						break;
					}
				}
				//���� � �������� ������ ��� ��������� �����, �� ���������, ���� �� ��������� ���� � ��������.
				if (Moves.Num() == 0) {
					this->BoardActor->GetAllMoves(Moves, this->ColorSide);
					if (Moves.Num() == 0) {
						//���� �� ���, �� �� ���������
						this->BoardActor->Lose(this);
					}
				}
			}
		} else {
			//���� �������� �� ������, �� �������� ��� ��������� ���� �������� ������
			AColumn* Column = Cast<AColumn>(HitResult.Actor.Get());
			if (Column != nullptr && this->SelectedFigure != nullptr) {
				TArray<UMoveFigure*> Moves;
				this->SelectedFigure->GetMoves(Moves);
				for (UMoveFigure* Move : Moves) {
					//���� ���� �� ����� ������ � ������������� ������, �� �����
					FFigureInfo MoveFigureInfo = Move->GetFigureInfoAfterMoving();
					if (MoveFigureInfo.Row == Column->GetRowPosition() && MoveFigureInfo.Column == Column->GetColumnPosition()) {
						Move->Move();
						break;
					}
				}
				//���� � �������� ������ ��� ��������� �����, �� ���������, ���� �� ��������� ���� � ��������.
				if (Moves.Num() == 0) {
					this->BoardActor->GetAllMoves(Moves, this->ColorSide);
					if (Moves.Num() == 0) {
						//���� �� ���, �� �� ���������
						this->BoardActor->Lose(this);
					}
				}
			}
		}
	}
}
void AChessPawn::OnClickToBoardClient_Implementation(FHitResult HitResult) {
	//���� ��� �� ���, �� ������ �� ������
	if (this->BoardActor != nullptr && this->BoardActor->GetPlayerPawnNextMove() == this) {
		//���� �������� �� ������, � ��� ���� ��� ����, �� ���������� ��� ��������� ����
		AFigure* Figure = Cast<AFigure>(HitResult.Actor.Get());
		if (Figure != nullptr) {
			if (this->ColorSide == Figure->GetColor()) {
				TArray<UMoveFigure*> Moves;
				Figure->GetMoves(Moves);
				this->BoardActor->DisplayMoves(Moves);
			} else {
				this->BoardActor->HideMoves();
			}
		} else {
			this->BoardActor->HideMoves();
		}
	}
}
void AChessPawn::BeginPlay() {
	Super::BeginPlay();
	if (this->HasAuthority()) {
		TArray<AActor*> Actors;
		//�������� ��������� �� ����� � �������������� ������
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ABoard::StaticClass(), Actors);
		if (Actors.Num() > 0) {
			this->BoardActor = Cast<ABoard>(Actors[0]);
			this->BoardActor->InitializePawn(this);
		}
	}
}
void AChessPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AChessPawn, ColorSide);
	DOREPLIFETIME(AChessPawn, BoardActor);
}
void AChessPawn::OnDirectionReplicated() {
	if (this->HasAuthority()) {
		//��������� ������ � ����������� �� �������, �� ������� ������ �����
		FVector Location = FVector::UpVector * 1800 +
			(this->ColorSide == EColorFigure::WHITE ? FVector::ForwardVector : FVector::BackwardVector) * -1100;
		this->SetActorLocation(Location);
		FRotator Rotation = (this->BoardActor->GetActorLocation() - Location).ToOrientationRotator();
		this->SetActorRotation(Rotation);
	}
}
void AChessPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) {
	Super::CalcCamera(DeltaTime, OutResult);
}
void AChessPawn::OnPawnEndPath_Implementation(int32 Row, int32 Column) {
	//���������� ���� ������ ������
	AChessPlayerController* PC = Cast<AChessPlayerController>(this->GetController());
	PC->SelectFigureTo(Row, Column);
}
void AChessPawn::WhaitNextMove_Implementation(){}
void AChessPawn::SelectedFigureSwap(TSubclassOf<AFigure> WhiteFigure, TSubclassOf<AFigure> BlackFigure,
	int32 Row, int32 Column) {
	//�������� ������ � ����������� �� �������
	AChessPlayerController* PC = Cast<AChessPlayerController>(this->GetController());
	PC->ChangeMenuWidget(nullptr);
	this->SwapPawnToFigure(this->ColorSide == EColorFigure::WHITE ? WhiteFigure : BlackFigure, Row, Column);
}
void AChessPawn::SwapPawnToFigure_Implementation(TSubclassOf<AFigure> Figure, int32 Row, int32 Column) {
	//������������� ������ �� �����
	this->BoardActor->SetFigure(Figure, Row, Column, this->ColorSide);
}
void AChessPawn::Win_Implementation() {
	//���������� ��������� � ���, ��� �� ��������
	auto PC = Cast<AChessPlayerController>(this->GetController());
	PC->ChangeMenuWidget(PC->WinUMG);
}
void AChessPawn::Lose_Implementation() {
	//���������� ��������� � ���, ��� �� ���������
	auto PC = Cast<AChessPlayerController>(this->GetController());
	PC->ChangeMenuWidget(PC->LoseUMG);
}