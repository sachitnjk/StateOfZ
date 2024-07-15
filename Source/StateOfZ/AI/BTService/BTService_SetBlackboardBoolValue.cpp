// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetBlackboardBoolValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetBlackboardBoolValue::UBTService_SetBlackboardBoolValue()
{
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_SetBlackboardBoolValue, BlackboardKey));
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_SetBlackboardBoolValue::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if(SetValueOnNodeEnter)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, ValueToSetOnEnter);
	}
}

void UBTService_SetBlackboardBoolValue::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	if(SetValueOnNodeExit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, ValueToSetOnExit);
	}
}
