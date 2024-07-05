// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionBox.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SearchBox.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInteractionBox::AInteractionBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(SceneComponent);
	
	SearchBoxComponent = CreateDefaultSubobject<USearchBox>(TEXT("SearchBoxComponent"));
	SearchBoxComponent->SetupAttachment(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	// WidgetComponent->SetVisibility(false);

	// SearchBoxComponent->SetUpUI(WidgetComponent);
}

// Called when the game starts or when spawned
void AInteractionBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

