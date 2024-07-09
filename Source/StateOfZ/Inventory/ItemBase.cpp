#include "ItemBase.h"
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

void AItemBase::Use()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Use Item called"));
}

void AItemBase::OnHover()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Hover Enabled On : %s"), *this->GetName());
}

void AItemBase::OnHoverDisable()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Hover Diabled On : %s"), *this->GetName());
}

void AItemBase::OnInteractStart(AStateOfZCharacter* PlayerChar)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interaction called on : %s"), *this->GetName());
	if(PlayerChar != nullptr)
	{
		PlayerChar->AddToPlayerInventory(this);
	}
	// Destroy(this);
}

void AItemBase::OnInteractOngoing()
{
	
}

void AItemBase::OnInteractStop()
{
	
}


