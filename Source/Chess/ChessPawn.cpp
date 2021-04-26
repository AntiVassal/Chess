// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Figure.h"
#include "Board.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Column.h"
#include "King.h"
#include "MoveFigure.h"
#include "ChessPlayerController.h"
#include "ChessGameMode.h"
AChessPawn::AChessPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	this->camera = this->CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->SetRootComponent(this->camera);
	this->bReplicates = true;
}

void AChessPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AChessPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// лик по доске
	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AChessPawn::TriggerClick);
}
void AChessPawn::TriggerClick()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		//“расировка луча
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
		//≈сли лучь столкнулс€ с доской или фигурой, то выполн€ем необходимые действи€
		this->clickToBoard(HitResult);
		this->clickToBoardClient(HitResult);
	}
}
void AChessPawn::clickToBoard_Implementation(FHitResult HitResult) {
	//≈сли ход не наш, то ничего не делаем
	if (this->board != nullptr && this->board->getNextMovePawn() == this) {
		AFigure* figure = Cast<AFigure>(HitResult.Actor.Get());
		if (figure != nullptr) {
			if (this->selectedFigure == nullptr || this->direction == figure->getDirection()) {
				//≈сли кликнули по фигуре, и при этом она наша, то выбираем еЄ дл€ хода
				this->selectedFigure = figure;
			} else {
				//≈сли мы кликнули по фигуре противника, то получаем все возможные ходы выбраной фигуры
				TArray<UMoveFigure*> moves;
				this->selectedFigure->getMoves(moves);
				for (auto move : moves) {
					if (move->toRow() == this->board->getRow(figure) && 
						move->toColumn() == this->board->getColumn(figure)) {
						//≈сли один из ходов совпал с расположением фигуры противника, то бьЄм еЄ
						move->move();;
						break;
					}
				}
				//≈сли у выбраной фигуры нет возможных ходов, то провер€ем, есть ли возможные ходы в принцыпе.
				if (moves.Num() == 0) {
					this->board->getAllMoves(moves, this->direction);
					if (moves.Num() == 0) {
						//≈сли их нет, то мы проиграли
						this->board->lose(this);
					}
				}
			}
		} else {
			//≈сли кликнули по клетке, то получаем все возможные ходы выбраной фигуры
			AColumn* column = Cast<AColumn>(HitResult.Actor.Get());
			if (column != nullptr && this->selectedFigure != nullptr) {
				TArray<UMoveFigure*> moves;
				this->selectedFigure->getMoves(moves);
				for (auto move : moves) {
					//≈сли один из ходов совпал с расположением клетки, то бьЄм еЄ
					if (move->toRow() == column->getRowPosition() && move->toColumn() == column->getColumnPosition()) {
						move->move();
						break;
					}
				}
				//≈сли у выбраной фигуры нет возможных ходов, то провер€ем, есть ли возможные ходы в принцыпе.
				if (moves.Num() == 0) {
					this->board->getAllMoves(moves, this->direction);
					if (moves.Num() == 0) {
						//≈сли их нет, то мы проиграли
						this->board->lose(this);
					}
				}
			}
		}
	}
}
void AChessPawn::clickToBoardClient_Implementation(FHitResult HitResult) {
	//≈сли ход не наш, то ничего не делаем
	if (this->board != nullptr && this->board->getNextMovePawn() == this) {
		//≈сли кликнули по фигуре, и при этом она наша, то отображаем все возможные ходы
		AFigure* figure = Cast<AFigure>(HitResult.Actor.Get());
		if (figure != nullptr) {
			if (this->direction == figure->getDirection()) {
				TArray<UMoveFigure*> moves;
				figure->getMoves(moves);
				this->board->displayMoves(moves);
			} else {
				this->board->hideMoves();
			}
		} else {
			this->board->hideMoves();
		}
	}
}
void AChessPawn::BeginPlay() {
	Super::BeginPlay();
	if (this->HasAuthority()) {
		TArray<AActor*> actors;
		//ѕолучаем указатель на доску и инициализируем игрока
		UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ABoard::StaticClass(), actors);
		if (actors.Num() > 0) {
			this->board = Cast<ABoard>(actors[0]);
			this->board->initializePawn(this);
		}
	}
}
void AChessPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AChessPawn, direction);
	DOREPLIFETIME(AChessPawn, board);
}
void AChessPawn::onDirectionReplicated() {
	if (this->HasAuthority()) {
		//–азмещаем камеру в зависимости от стороны, за которую играет игрок
		auto location = FVector::UpVector * 1800 +
			(this->direction == DirectionFigure::WHITE ? FVector::ForwardVector : FVector::BackwardVector) * -1100;
		this->SetActorLocation(location);
		auto rotation = (this->board->GetActorLocation() - location).ToOrientationRotator();
		this->SetActorRotation(rotation);
	}
}
void AChessPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) {
	Super::CalcCamera(DeltaTime, OutResult);
}
void AChessPawn::pawnEndPath_Implementation(int32 row, int32 column) {
	//ќтобразить меню выбора фигуры
	auto PC = Cast<AChessPlayerController>(this->GetController());
	PC->selectFigureTo(row, column);
}
void AChessPawn::whaitMove_Implementation(){}
void AChessPawn::selectedFigureSwap(TSubclassOf<AFigure> whiteFigure, TSubclassOf<AFigure> blackFigure, int32 row, int32 column) {
	//выбираем фигуру в зависимости от стороны
	auto PC = Cast<AChessPlayerController>(this->GetController());
	PC->ChangeMenuWidget(nullptr);
	this->swapPawnToFigure(this->direction == DirectionFigure::WHITE ? whiteFigure : blackFigure, row, column);
}
void AChessPawn::swapPawnToFigure_Implementation(TSubclassOf<AFigure> figure, int32 row, int32 column) {
	//”станавливаем фигуру на доску
	this->board->setFigure(figure, row, column, this->direction);
}
void AChessPawn::win_Implementation() {
	//ќтображаем сообщение о том, что мы выиграли
	auto PC = Cast<AChessPlayerController>(this->GetController());
	PC->ChangeMenuWidget(PC->winUMG);
}
void AChessPawn::lose_Implementation() {
	//ќтображаем сообщение о том, что мы проиграли
	auto PC = Cast<AChessPlayerController>(this->GetController());
	PC->ChangeMenuWidget(PC->loseUMG);
}