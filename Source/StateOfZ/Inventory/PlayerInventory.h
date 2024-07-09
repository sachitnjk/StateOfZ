#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "PlayerInventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEOFZ_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()
	
public:

	UPlayerInventory();

	void AddToInventory(AItemBase* Item);
};
