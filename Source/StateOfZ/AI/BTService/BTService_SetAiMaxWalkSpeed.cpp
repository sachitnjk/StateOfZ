// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetAiMaxWalkSpeed.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateOfZ/AI/BaseAiCharacter.h"

UBTService_SetAiMaxWalkSpeed::UBTService_SetAiMaxWalkSpeed()
{
	NodeName = TEXT("Set Ai Max Speed");
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_SetAiMaxWalkSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	ABaseAiCharacter* aiCharacter = Cast<ABaseAiCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(aiCharacter)
	{
		if(GoBackToOldSpeedOnNodeExit)
		{
			CachedWalkSpeed = aiCharacter->GetCharacterMovement()->MaxWalkSpeed;
		}
		aiCharacter->SetMaxWalkSpeed(AiMaxWalkSpeed);
	}
}

void UBTService_SetAiMaxWalkSpeed::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	if(GoBackToOldSpeedOnNodeExit)
	{
		ABaseAiCharacter* aiCharacter = Cast<ABaseAiCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if(aiCharacter)
		{
			aiCharacter->SetMaxWalkSpeed(CachedWalkSpeed);
		}
	}
}
