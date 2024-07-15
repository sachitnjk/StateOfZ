#include "ChaserAiController.h"

#include "StateOfZ/Player/StateOfZCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "StateOfZ/AI/EnemyEnumTypes.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

void AChaserAiController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::PerceptionUpdated(Actor, Stimulus);
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

void AChaserAiController::PerceptionForget(AActor* Actor)
{
	Super::PerceptionForget(Actor);
	if(Actor == CachedPlayer && CurrentStateCatch != EEnemyAiState::InvestigateSound)
	{
		UE_LOG(LogTemp, Display, TEXT("PLAYER FORGOTTEN"));
		ClearPlayerOnBlackboard();
		AiBlackboard->SetValueAsVector(BBK_InvestigationPosition, CachedPlayer->GetActorLocation());
		SetCurrentStateOnBlackboard(EEnemyAiState::InvestigateLastSeen);
	}
}
