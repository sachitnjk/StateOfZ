// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetEnemyAiState.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "StateOfZ/AI/EnemyEnumTypes.h"

UBTService_SetEnemyAiState::UBTService_SetEnemyAiState()
{
	NodeName = TEXT("Set Enemy Ai State");
	BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_SetEnemyAiState, BlackboardKey), StaticEnum<EEnemyAiState>());
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_SetEnemyAiState::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if(SetValueOnNodeEnter)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BlackboardKey.SelectedKeyName, static_cast<uint8>(StateToSetOnEnter));
	}
}

void UBTService_SetEnemyAiState::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	if(SetValueOnNodeExit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BlackboardKey.SelectedKeyName, static_cast<uint8>(StateToSetOnExit));
	}
}
