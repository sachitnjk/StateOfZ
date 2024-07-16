// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetBlackboardBoolValue.generated.h"

/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTService_SetBlackboardBoolValue : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetBlackboardBoolValue();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool SetValueOnNodeEnter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool ValueToSetOnEnter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool SetValueOnNodeExit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool ValueToSetOnExit;
};
