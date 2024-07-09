#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "StateOfZ/Interfaces/Interactable.h"
#include "ItemBase.generated.h"

UCLASS()
class STATEOFZ_API AItemBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AItemBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ItemWeight;
	
	virtual void Use();

	// functions from IInteractable interface
	virtual void OnHover() override;
	virtual void OnHoverDisable() override;
	virtual void OnInteractStart(AStateOfZCharacter* PlayerChar) override;
	virtual void OnInteractOngoing() override;
	virtual void OnInteractStop() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetComponent;

	
};

