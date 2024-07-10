// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToWithFixedSpeed.generated.h"

/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTTask_MoveToWithFixedSpeed : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MoveToWithFixedSpeed();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	float AiMaxWalkSpeed = 250.f;
};
