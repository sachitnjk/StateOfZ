// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchBox.h"
#include "Components/WidgetComponent.h"
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
	if(PressKeyPopUpWidget != nullptr)
	{
		PressKeyPopUpWidget->SetVisibility(true);
	}
}

void USearchBox::OnHoverDisable()
{
	if (PressKeyPopUpWidget)
	{
		PressKeyPopUpWidget->SetVisibility(false);
	}
}

void USearchBox::OnSearchingUI()
{
	if(SearchingPopUpWidget)
	{
		OnHoverDisable();
		SearchingPopUpWidget->SetVisibility(true);
	}
}

void USearchBox::OnSearchingUIStop()
{
	if(SearchingPopUpWidget)
	{
		SearchingPopUpWidget->SetVisibility(false);
		OnHover();
	}
}

void USearchBox::OnInteractStart()
{
	// if(!isOpen)
	// {
	// 	isOpen = true;
	// }
	// else
	// {
	// 	isOpen = false;
	// }
	//
	// UE_LOG(LogTemplateCharacter, Log, TEXT("going here"));
	// UE_LOG(LogTemplateCharacter, Log, TEXT("Interact called on this, open status: %s"), isOpen ? TEXT("true") : TEXT("false"));
	if(SearchingPopUpWidget)
	{
		OnHoverDisable();
		SearchingPopUpWidget->SetVisibility(true);
	}
}

void USearchBox::OnInteractOngoing()
{
	
}


void USearchBox::OnInteractStop()
{
	if(SearchingPopUpWidget)
	{
		SearchingPopUpWidget->SetVisibility(false);
		OnHover();
	}
}


void USearchBox::SetUpUI(UWidgetComponent* PressKeyPopUp)
{
	if(PressKeyPopUp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The UI set up is called with a null widget on the seach box"));
		return;	
	}
	
	PressKeyPopUpWidget = PressKeyPopUp;
	PressKeyPopUpWidget->SetVisibility(false);
}

void USearchBox::SetUpSearchingTextUI(UWidgetComponent* SearchingTextWidget)
{
	if(SearchingTextWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The UI set up is called with a null widget on the seach box"));
		return;	
	}
	
	SearchingPopUpWidget = SearchingTextWidget;
	SearchingPopUpWidget->SetVisibility(false);
}
