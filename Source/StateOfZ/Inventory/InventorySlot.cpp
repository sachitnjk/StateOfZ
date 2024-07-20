#include "InventorySlot.h"
#include "ItemBase.h"

UInventorySlot::UInventorySlot()
{
	Item = nullptr;
}


bool UInventorySlot::CanAcceptItem(AItemBase* InvItem)
{
	return (Item == nullptr && slotType == InvItem->GetItemSlotType());
}

void UInventorySlot::AddItem(AItemBase* InvItem)
{
	if(CanAcceptItem(InvItem))
	{
		Item = InvItem;
	}
}

void UInventorySlot::RemoveItem()
{
	if(Item != nullptr)
	{
		Item = nullptr;
	}
}


