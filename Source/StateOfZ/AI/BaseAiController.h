// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAiController.generated.h"

class ABaseAiCharacter;
class AStateOfZCharacter;
class UAIPerceptionComponent;

UCLASS()
class STATEOFZ_API ABaseAiController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAiController();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetPlayerOnBlackboard();
	void ClearPlayerOnBlackboard();
	
protected:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Components")
	UAIPerceptionComponent* AiPerceptionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	UBehaviorTree* AiBehavior;

	UBlackboardComponent* AiBlackboard;
	ABaseAiCharacter* CachedAiAgent;
	AStateOfZCharacter* CachedPlayer;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	const FName BBK_Player = FName("Player");
	const FName BBK_StartingLocation = FName("StartingLocation");
};
