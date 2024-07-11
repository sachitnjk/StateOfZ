// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiCharacter.h"

#include "BaseAiController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"


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

	TeamId = FGenericTeamId(IdOfTeam);
	AiPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAiCharacter::PerceptionUpdated);
	CachedController = Cast<ABaseAiController>(GetController());
}

void ABaseAiCharacter::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			if(CachedController != nullptr)
			{
				CachedController->SetPlayerOnBlackboard();
			}
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			// Handle updates to the hearing sense
		}
	}
	else
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			if(CachedController != nullptr)
			{
				CachedController->ClearPlayerOnBlackboard();
			}
		}
	}
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
