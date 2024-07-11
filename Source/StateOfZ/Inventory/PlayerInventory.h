#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "StateOfZ/Structs/InventoryItemData.h"
#include "PlayerInventory.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEOFZ_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()
	
public:

	UPlayerInventory();

	void AddToInventory(AItemBase* Item);
	
	TArray<FInventoryItemData> InventoryItemDataList;

private:

	void NewItemAdd(AItemBase* ItemToAdd);
	void StackItem(FInventoryItemData& ItemToStackData, AItemBase* ItemToStack);
};
