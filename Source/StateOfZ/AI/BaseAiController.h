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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Components")
	UAIPerceptionComponent* AiPerceptionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	UBehaviorTree* AiBehavior;

	UBlackboardComponent* AiBlackboard;
	ABaseAiCharacter* CachedAiAgent;
	AStateOfZCharacter* CachedPlayer;
	EEnemyAiState CurrentStateCatch;

	FName BBK_Player = FName("Player");
	FName BBK_CurrentState = FName("CurrentState");
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	virtual void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = true))
	virtual void PerceptionForget(AActor* Actor);
};
