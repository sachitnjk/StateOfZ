// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiController.h"

#include "BaseAiCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StateOfZ/Player/StateOfZCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

ABaseAiController::ABaseAiController()
{
	AiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
}

void ABaseAiController::BeginPlay()
{
	Super::BeginPlay();
	CachedAiAgent = Cast<ABaseAiCharacter>(GetPawn());
	if(AiBehavior)
	{
		RunBehaviorTree(AiBehavior);
		AiBlackboard = GetBlackboardComponent();
		AiBlackboard->SetValueAsVector(BBK_StartingLocation, GetPawn()->GetActorLocation());
		CachedPlayer = Cast<AStateOfZCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}
	AiPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAiController::PerceptionUpdated);
}

void ABaseAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseAiController::SetPlayerOnBlackboard()
{
	if(CachedPlayer != nullptr && AiBlackboard != nullptr)
	{
		AiBlackboard->SetValueAsObject(BBK_Player, CachedPlayer);
	}
}

void ABaseAiController::ClearPlayerOnBlackboard()
{
	if(AiBlackboard != nullptr)
	{
		AiBlackboard->ClearValue(BBK_Player);
	}
}


void ABaseAiController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			SetPlayerOnBlackboard();
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			// Handle updates to the hearing sense
		}
	}
	else
	{
		ClearPlayerOnBlackboard();
	}
}

ETeamAttitude::Type ABaseAiController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if(CachedAiAgent == nullptr)
	{
		return ETeamAttitude::Neutral;
	}
	
	const APawn* otherPawn = Cast<APawn>(&Other);
	if(otherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* teamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if(teamAgent == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId OtherActorTeamId = teamAgent->GetGenericTeamId();
	if(OtherActorTeamId == CachedAiAgent->GetGenericTeamId())
	{
		return ETeamAttitude::Friendly;
	}
	
	return ETeamAttitude::Hostile;
}
