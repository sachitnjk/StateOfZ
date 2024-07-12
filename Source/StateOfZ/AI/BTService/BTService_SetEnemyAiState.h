// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetEnemyAiState.generated.h"

enum class EEnemyAiState : uint8;
/**
 * 
 */
UCLASS()
class STATEOFZ_API UBTService_SetEnemyAiState : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetEnemyAiState();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool SetValueOnNodeEnter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	EEnemyAiState StateToSetOnEnter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	bool SetValueOnNodeExit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Blackboard, meta=(AllowPrivateAccess=true))
	EEnemyAiState StateToSetOnExit;
};
