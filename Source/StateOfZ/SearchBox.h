// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SearchBox.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEOFZ_API USearchBox : public UBoxComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	USearchBox();

	void OnHover();
	void OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
