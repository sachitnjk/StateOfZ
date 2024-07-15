// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Interfaces/Interactable.h"
#include "Player/StateOfZCharacter.h"
#include "Structs/InventoryItemData.h"
#include "SearchBox.generated.h"

class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEOFZ_API USearchBox : public UBoxComponent, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USearchBox();

	// functions from IInteractable interface
	virtual void OnHover() override;
	virtual void OnHoverDisable() override;
	virtual void OnInteractStart(AStateOfZCharacter* PlayerChar) override;
	virtual void OnInteractOngoing() override;
	virtual void OnInteractStop() override;
	virtual void SetOpenedStatus(bool isBoxOpen) override;
	virtual bool GetOpenedStatus() override;

	void OnSearchingUI();
	void OnSearchingUIStop();

	UFUNCTION(BlueprintCallable)
	void SetUpUI(UWidgetComponent* PressKeyPopUp);

	void SetUpSearchingTextUI(UWidgetComponent* SearchingTextWidget);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool isOpen;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UWidgetComponent* PressKeyPopUpWidget;
	
	UWidgetComponent* SearchingPopUpWidget;
};
