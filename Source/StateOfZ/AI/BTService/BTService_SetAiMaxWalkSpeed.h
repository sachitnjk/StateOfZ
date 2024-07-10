// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetAiMaxWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTService_SetAiMaxWalkSpeed : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetAiMaxWalkSpeed();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	bool GoBackToOldSpeedOnNodeExit = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	float AiMaxWalkSpeed = 250.f;

	float CachedWalkSpeed;
};
