// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetRandomLocationInSphere.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetRandomLocationInSphere::UBTTask_SetRandomLocationInSphere()
{
	NodeName = TEXT("Set Random Location In Sphere");
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetRandomLocationInSphere, BlackboardKey));
}

EBTNodeResult::Type UBTTask_SetRandomLocationInSphere::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FVector aiPawnLocation =  OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	FNavLocation recievedRandomNavLocation;
	if(NavSys->GetRandomPointInNavigableRadius(aiPawnLocation, SphereRadius,recievedRandomNavLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, recievedRandomNavLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
