// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchBox.h"
#include "Components/WidgetComponent.h"
#include "Player/StateOfZCharacter.h"

// Sets default values
USearchBox::USearchBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void USearchBox::BeginPlay()
{
	Super::BeginPlay();

	isOpen = false;
	PlayerScript = nullptr;
}

void USearchBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PlayerScript != nullptr && InteractionProgressBar != nullptr)
	{
		float InteractProgress = PlayerScript->GetInteractProgress();
		InteractionProgressBar->SetPercent(InteractProgress);
	}
}


void USearchBox::OnHover()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Hovering on this"));
	if(!isOpen)
	{
		if(PressKeyPopUpWidget)
		{
			PressKeyPopUpWidget->SetVisibility(true);
		}
		if(BoxOpenedHoverWidget)
		{
			BoxOpenedHoverWidget->SetVisibility(false);
		}
	}
	else
	{
		if(BoxOpenedHoverWidget)
		{
			BoxOpenedHoverWidget->SetVisibility(true);
		}
		if(PressKeyPopUpWidget)
		{
			PressKeyPopUpWidget->SetVisibility(false);
		}
	}
}

void USearchBox::OnHoverDisable()
{
	if(!isOpen)
	{
		if(PressKeyPopUpWidget)
		{
			PressKeyPopUpWidget->SetVisibility(false);
		}
		if(BoxOpenedHoverWidget)
		{
			BoxOpenedHoverWidget->SetVisibility(false);
		}
	}
	else
	{
		if(BoxOpenedHoverWidget)
		{
			BoxOpenedHoverWidget->SetVisibility(false);
		}
		if(PressKeyPopUpWidget)
		{
			PressKeyPopUpWidget->SetVisibility(false);
		}
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

void USearchBox::OnInteractStart(AStateOfZCharacter* PlayerChar)
{
	PlayerScript = PlayerChar;
	if(!isOpen)
	{
		if(SearchingPopUpWidget)
		{
			OnHoverDisable();
			SearchingPopUpWidget->SetVisibility(true);
		}
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
	PlayerScript = nullptr;
}

bool USearchBox::GetOpenedStatus()
{
	return isOpen;
}

void USearchBox::SetOpenedStatus(bool isBoxOpen)
{
	isOpen = isBoxOpen;
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

	if(SearchingPopUpWidget)
	{
		UUserWidget* SearchingUserWidget = Cast<UUserWidget>(SearchingPopUpWidget->GetUserWidgetObject());
		if(SearchingUserWidget)
		{
			InteractionProgressBar = Cast<UProgressBar>(SearchingUserWidget->GetWidgetFromName(TEXT("InteractionProgressBar")));
			if(!InteractionProgressBar)
			{
				UE_LOG(LogTemplateCharacter, Log, TEXT("progress Bar Found"));
			}
		}
	}
}

void USearchBox::SetUpBoxOpenedHoverUI(UWidgetComponent* BoxOpenedWidget)
{
	if(BoxOpenedWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The UI set up is called with a null widget on the seach box"));
		return;	
	}
	BoxOpenedHoverWidget = BoxOpenedWidget;
	BoxOpenedHoverWidget->SetVisibility(false);
}
