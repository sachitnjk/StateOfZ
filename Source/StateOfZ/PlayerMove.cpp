// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"

// Sets default values
APlayerMove::APlayerMove()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerMove::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerMove::SpawnActor()
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	GetWorld()->SpawnActor<AActor>(actorBPToSpawn, GetActorTransform(), spawnParams);
}

