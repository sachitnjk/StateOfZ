#include "PlayerInventory.h"

#include "Algo/ForEach.h"
#include "StateOfZ/Player/StateOfZCharacter.h"
#include "Engine/Engine.h"
#include "StateOfZ/Structs/InventoryItemData.h"

UPlayerInventory::UPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInventory::AddToInventory(AItemBase* Item)
{
	if(Item)
	{
		bool bItemFound = false;
		
		for (FInventoryItemData& InvItemData : InventoryItemDataList)
		{
			if(InvItemData.InventoryItem && InvItemData.InventoryItem->ItemName == Item->ItemName)
			{
				UE_LOG(LogTemplateCharacter, Log, TEXT("Going here"));
				StackItem(InvItemData, Item);
				bItemFound = true;
				break;
			}
		}

		if(!bItemFound)
		{
			NewItemAdd(Item);
		}

		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Item Found: %s"), bItemFound ? TEXT("True") : TEXT("False")));

		for (FInventoryItemData& InvItemData : InventoryItemDataList)
		{
			if (InvItemData.InventoryItem)
			{
				FString ItemName = InvItemData.InventoryItem->ItemName;
				int ItemCount = InvItemData.ItemCount;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Inventory Item: %s, Count: %d"), *ItemName, ItemCount));
			}
		}
	}
}

void UPlayerInventory::NewItemAdd(AItemBase* ItemToAdd)
{
	FInventoryItemData NewItem;
	NewItem.InventoryItem = ItemToAdd;
	NewItem.ItemCount = 1;

	InventoryItemDataList.Add(NewItem);
}

void UPlayerInventory::StackItem(FInventoryItemData& ItemToStackData, AItemBase* ItemToStack)
{
	if(ItemToStackData.ItemCount < ItemToStack->maxItemStackCount)
	{
		ItemToStackData.ItemCount++;
	}
}

