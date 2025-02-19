// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiController.h"

#include "BaseAiCharacter.h"
#include "EnemyEnumTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StateOfZ/Player/StateOfZCharacter.h"
#include "Perception/AIPerceptionComponent.h"

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
		
		checkf(AiBlackboard != nullptr, TEXT("The Blackboard Component is null, set the black board on the behavior tree assigned to the ai controller"));
		
		CachedPlayer = Cast<AStateOfZCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		AiPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAiController::PerceptionUpdated);
		AiPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, & ABaseAiController::PerceptionForget);
		CurrentStateCatch = EEnemyAiState::Default;
	}
}

void ABaseAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseAiController::SetPlayerOnBlackboard()
{
	if(CachedPlayer != nullptr)
	{
		AiBlackboard->SetValueAsObject(BBK_Player, CachedPlayer);
	}
}

void ABaseAiController::ClearPlayerOnBlackboard()
{
	AiBlackboard->ClearValue(BBK_Player);
}

void ABaseAiController::SetCurrentStateOnBlackboard(EEnemyAiState StateToSet)
{
	CurrentStateCatch = StateToSet;
	AiBlackboard->SetValueAsEnum(BBK_CurrentState,  static_cast<uint8>(StateToSet));
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

void ABaseAiController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}

void ABaseAiController::PerceptionForget(AActor* Actor)
{
}
