// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetRandomLocationInSphere.generated.h"

/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTTask_SetRandomLocationInSphere : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SetRandomLocationInSphere();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float SphereRadius = 500.f;
};
