#include "PlayerInventory.h"
#include "StateOfZ/Player/StateOfZCharacter.h"
#include "Engine/Engine.h"

UPlayerInventory::UPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInventory::AddToInventory(AItemBase* Item)
{
	if(Item)
	{
		//Change to .AddUnique for inbuilt duplicate check
		InventoryItemList.Add(Item);

		// --Logging the list on screen-- 
		 // for (AItemBase* InventoryItem : InventoryItemList)
		 // {
		 // 	if (InventoryItem)
		 // 	{
		 // 		FString ItemName = InventoryItem->ItemName;
		 // 		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Inventory Item: %s"), *ItemName));
		 // 	}
		 // }
	}
}

