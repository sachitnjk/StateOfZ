// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsInCertainAiState.generated.h"

enum class EEnemyAiState : uint8;
/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTDecorator_IsInCertainAiState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_IsInCertainAiState();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool CheckForNotEquals;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	EEnemyAiState StateToCompareTo;
};
