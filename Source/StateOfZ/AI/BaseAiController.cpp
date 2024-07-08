// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAiController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ABaseAiController::BeginPlay()
{
	Super::BeginPlay();
	if(AiBehavior)
	{
		RunBehaviorTree(AiBehavior);
		AiBlackboard = GetBlackboardComponent();
		AiBlackboard->SetValueAsVector(BBK_StartingLocation, GetPawn()->GetActorLocation());
		APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if(playerPawn != nullptr)
		{
			AiBlackboard->SetValueAsObject(BBK_Player, playerPawn);
		}
	}
}

void ABaseAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
