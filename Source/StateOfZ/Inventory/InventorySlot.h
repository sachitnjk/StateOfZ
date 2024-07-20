#pragma once

#include "CoreMinimal.h"
#include "StateOfZ/Eums/ItemSlotType.h"
#include "InventorySlot.generated.h"

class AItemBase;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STATEOFZ_API UInventorySlot: public UObject
{
	GENERATED_BODY()
	
public:
	UInventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EItemSlotType slotType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AItemBase* Item;

	bool CanAcceptItem(AItemBase* InvItem);
	void AddItem(AItemBase* InvItem);
	void RemoveItem();
};
