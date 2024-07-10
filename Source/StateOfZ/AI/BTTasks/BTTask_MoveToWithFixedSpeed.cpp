// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToWithFixedSpeed.h"

#include "AIController.h"
#include "StateOfZ/AI/BaseAiCharacter.h"

UBTTask_MoveToWithFixedSpeed::UBTTask_MoveToWithFixedSpeed()
{
	NodeName = TEXT("Move To With Fixed Speed");
}

EBTNodeResult::Type UBTTask_MoveToWithFixedSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseAiCharacter* aiCharacter = Cast<ABaseAiCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(aiCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	aiCharacter->SetMaxWalkSpeed(AiMaxWalkSpeed);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
