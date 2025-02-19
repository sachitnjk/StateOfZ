﻿#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "StateOfZ/Eums/ItemSlotType.h"
#include "StateOfZ/Interfaces/Interactable.h"
#include "ItemBase.generated.h"

UCLASS()
class STATEOFZ_API AItemBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemSlotType ItemSlotType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int maxItemStackCount;

	UFUNCTION()
	EItemSlotType GetItemSlotType();
	
	UWidgetComponent* HoverDisplayWidget;
	
	void SetUpUI(UWidgetComponent* PopUpUI);
	void SetUpItemIcon();
	virtual void Use();
	// functions from IInteractable interface
	virtual void OnHover() override;
	virtual void OnHoverDisable() override;
	virtual void OnInteractStart(AStateOfZCharacter* PlayerChar) override;
	virtual void OnInteractOngoing() override;
	virtual void OnInteractStop() override;

	//Unused
	virtual void SetOpenedStatus(bool isBoxOpen) override;
	virtual bool GetOpenedStatus() override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetComponent;

	
};

