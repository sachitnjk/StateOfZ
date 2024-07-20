#include "ItemBase.h"

#include "IDetailTreeNode.h"
#include "Components/Image.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "StateOfZ/Player/StateOfZCharacter.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(SceneComponent);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	if(maxItemStackCount <= 0)
	{
		//Setting default value for maxItemStackCount if not set in editor
		maxItemStackCount = 1;
	}
	
	SetUpUI(WidgetComponent);
	SetUpItemIcon();
}


void AItemBase::Use()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Use Item called"));
}

void AItemBase::OnHover()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Hover Enabled On : %s"), *this->GetName());
	HoverDisplayWidget->SetVisibility(true);
}

void AItemBase::OnHoverDisable()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Hover Diabled On : %s"), *this->GetName());
	HoverDisplayWidget->SetVisibility(false);
}

void AItemBase::OnInteractStart(AStateOfZCharacter* PlayerChar)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interaction called on : %s"), *this->GetName());
	if(PlayerChar != nullptr)
	{
		PlayerChar->AddToPlayerInventory(this);
		Destroy();
	}
}

//-----Unused interface functions-----//

bool AItemBase::GetOpenedStatus()
{
	return false;	
}

void AItemBase::SetOpenedStatus(bool isBoxOpen)
{
	return;
}

void AItemBase::OnInteractOngoing()
{
	return;
}

void AItemBase::OnInteractStop()
{
	return;
}

//----------//

void AItemBase::SetUpUI(UWidgetComponent* PopUpUI)
{
	if(PopUpUI == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The UI set up is called with a null widget on the seach box"));
		return;	
	}
	
	HoverDisplayWidget = PopUpUI;
	HoverDisplayWidget->SetVisibility(false);
}

void AItemBase::SetUpItemIcon()
{
	if(WidgetComponent == nullptr || ItemIcon == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("WidgetComponent or ItemIcon is null"));
		return;
	}

	UUserWidget* UserWidget = WidgetComponent->GetUserWidgetObject();
	if(UserWidget)
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("UserWidget found in WidgetComponent"));
		UImage* ItemImage = Cast<UImage>(UserWidget->GetWidgetFromName("ItemIconImage"));
		if(ItemImage)
		{
			UE_LOG(LogTemplateCharacter, Log, TEXT("ItemImage found in casted UserWidget"));
			ItemImage->SetBrushFromTexture(ItemIcon);	
		}
	}
}

EItemSlotType AItemBase::GetItemSlotType()
{
	return ItemSlotType;
}


