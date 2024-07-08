// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAiController.generated.h"

/**
 * 
 */
UCLASS()
class STATEOFZ_API ABaseAiController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	UBehaviorTree* AiBehavior;

	UBlackboardComponent* AiBlackboard;

	const FName BBK_Player = FName("Player");
	const FName BBK_StartingLocation = FName("StartingLocation");
	
};
