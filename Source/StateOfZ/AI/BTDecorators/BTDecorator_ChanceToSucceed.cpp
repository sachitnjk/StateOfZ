// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_ChanceToSucceed.h"

UBTDecorator_ChanceToSucceed::UBTDecorator_ChanceToSucceed()
{
	NodeName = TEXT("Chance To Succeed");
}

bool UBTDecorator_ChanceToSucceed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	float chosenNumber = FMath::RandRange(0.f,100.f);
	if(chosenNumber < ChanceToSucceeedInPecentage)
	{
		return true;
	}
	return false;
}
