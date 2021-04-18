// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessPawn.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Figure.h"
#include "Board.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
AChessPawn::AChessPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AChessPawn::TriggerClick);
}

void AChessPawn::TriggerClick()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
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
		AFigure* figure = Cast<AFigure>(HitResult.Actor.Get());
		if (figure != nullptr && this->board != nullptr) {
			this->board->selectFigure(figure->getPositionRow(), figure->getPositionColumn(), this->direction);
		}
		ABoard* lboard = Cast<ABoard>(HitResult.Actor.Get());
		if (lboard != nullptr) {
			lboard->click(HitResult.Location);
		}
	}
}
void AChessPawn::BeginPlay() {
	Super::BeginPlay();
	if (this->HasAuthority()) {
		TArray<AActor*> actors;
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
		auto location = FVector::UpVector * 2000 +
			(this->direction == DirectionFigure::WHITE ? FVector::ForwardVector : FVector::BackwardVector) * -1100;
		this->SetActorLocation(location);
		auto rotation = (this->board->GetActorLocation() - location).ToOrientationRotator();
		this->SetActorRotation(rotation);
		UEnum* uenum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true);
		UE_LOG(LogTemp, Display, TEXT("Test: %s %s"),
			*this->GetActorLabel(),
			*uenum->GetNameByValue((int64)this->GetLocalRole()).ToString());
		uenum = FindObject<UEnum>(ANY_PACKAGE, TEXT("DirectionFigure"), true);
		UE_LOG(LogTemp, Display, TEXT("Test: %s %s"),
			*this->GetActorLabel(),
			*uenum->GetNameByValue((int64)this->direction).ToString()
		);
	}
}