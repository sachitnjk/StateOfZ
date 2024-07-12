// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInCertainAiState.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "StateOfZ/AI/EnemyEnumTypes.h"

UBTDecorator_IsInCertainAiState::UBTDecorator_IsInCertainAiState()
{
	NodeName = TEXT("Is In Certain AiState?");
	BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsInCertainAiState, BlackboardKey), StaticEnum<EEnemyAiState>());
}

bool UBTDecorator_IsInCertainAiState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();
	if(blackboardComponent != nullptr)
	{
		EEnemyAiState currentAiState = static_cast<EEnemyAiState>(blackboardComponent->GetValueAsEnum(BlackboardKey.SelectedKeyName));
		
		return CheckForNotEquals ? currentAiState != StateToCompareTo : currentAiState == StateToCompareTo;
	}

	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
