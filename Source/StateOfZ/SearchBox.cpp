// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchBox.h"

#include "Player/StateOfZCharacter.h"

// Sets default values
USearchBox::USearchBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void USearchBox::BeginPlay()
{
	Super::BeginPlay();

	isOpen = false;
}

void USearchBox::OnHover()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Hovering on this"));
}

void USearchBox::OnInteract()
{
	if(!isOpen)
	{
		isOpen = true;
	}
	else
	{
		isOpen = false;
	}

	UE_LOG(LogTemplateCharacter, Log, TEXT("going here"));
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interact called on this, open status: %s"), isOpen ? TEXT("true") : TEXT("false"));
}
