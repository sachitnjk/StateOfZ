// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ChanceToSucceed.generated.h"

/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTDecorator_ChanceToSucceed : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_ChanceToSucceed();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true, ClampMin = 1, ClampMax = 99,  UIMin= 1, UIMax = 99))
	int ChanceToSucceeedInPecentage = 30;
};
