// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiController.h"

#include "BaseAiCharacter.h"
#include "EnemyEnumTypes.h"
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
		
		checkf(AiBlackboard != nullptr, TEXT("The Blackboard Component is null, set the black board on the behavior tree assigned to the ai controller"));
		
		AiBlackboard->SetValueAsVector(BBK_StartingLocation, GetPawn()->GetActorLocation());
		CachedPlayer = Cast<AStateOfZCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		
		AiPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAiController::PerceptionUpdated);
		AiPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, & ABaseAiController::PerceptionForget);
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


void ABaseAiController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			SetPlayerOnBlackboard();
			SetCurrentStateOnBlackboard(EEnemyAiState::Chase);
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{
			AiBlackboard->SetValueAsBool(BBK_NewSoundRegistered, true);
			AiBlackboard->SetValueAsVector(BBK_InvestigationPosition, Stimulus.StimulusLocation);
			SetCurrentStateOnBlackboard(EEnemyAiState::InvestigateSound);
		}
	}
	else
	{
		//Out of any of the perception ranges.
	}
}

void ABaseAiController::PerceptionForget(AActor* Actor)
{
	if(Actor == CachedPlayer && CurrentStateCatch != EEnemyAiState::InvestigateSound)
	{
		UE_LOG(LogTemp, Display, TEXT("PLAYER FORGOTTEN"));
		ClearPlayerOnBlackboard();
		AiBlackboard->SetValueAsVector(BBK_InvestigationPosition, CachedPlayer->GetActorLocation());
		SetCurrentStateOnBlackboard(EEnemyAiState::InvestigateLastSeen);
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
