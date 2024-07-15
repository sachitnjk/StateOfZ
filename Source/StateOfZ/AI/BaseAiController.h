// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAiController.generated.h"

enum class EEnemyAiState : uint8;
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
	void SetCurrentStateOnBlackboard(EEnemyAiState StateToSet);
	
protected:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	void PerceptionForget(AActor* Actor);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Components")
	UAIPerceptionComponent* AiPerceptionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	UBehaviorTree* AiBehavior;

	UBlackboardComponent* AiBlackboard;
	ABaseAiCharacter* CachedAiAgent;
	AStateOfZCharacter* CachedPlayer;
	EEnemyAiState CurrentStateCatch;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	const FName BBK_Player = FName("Player");
	const FName BBK_StartingLocation = FName("StartingLocation");
	const FName BBK_CurrentState = FName("CurrentState");
	const FName BBK_InvestigationPosition = FName("InvestigationPosition");
};
