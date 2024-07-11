// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiCharacter.h"
#include "BaseAiController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABaseAiCharacter::ABaseAiCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseAiCharacter::BeginPlay()
{
	Super::BeginPlay();

	TeamId = FGenericTeamId(IdOfTeam);
	CachedController = Cast<ABaseAiController>(GetController());
}

// Called every frame
void ABaseAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAiCharacter::SetMaxWalkSpeed(float MaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}
