// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "BaseAiCharacter.generated.h"

class UAIPerceptionComponent;

UCLASS()
class STATEOFZ_API ABaseAiCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="Components")
	UAIPerceptionComponent* AiPerceptionComponent;

	FGenericTeamId TeamId;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetMaxWalkSpeed(float MaxWalkSpeed);
	
	//Team Id interface sutff
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IdOfTeam = 1;
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	
	FORCEINLINE UAIPerceptionComponent* GetAiPerceptionComponent() { return AiPerceptionComponent; }
};
