// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"


// Sets default values
ABaseAiCharacter::ABaseAiCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
}

// Called when the game starts or when spawned
void ABaseAiCharacter::BeginPlay()
{
	Super::BeginPlay();
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
