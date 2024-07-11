// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiController.h"

#include "BaseAiCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StateOfZ/Player/StateOfZCharacter.h"

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
