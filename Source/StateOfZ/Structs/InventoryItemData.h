#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.generated.h"

class AItemBase;

USTRUCT(BlueprintType)
struct FInventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "InventoryItems")
	AItemBase* InventoryItem;

	UPROPERTY(EditAnywhere, Category = "InventoryItems")
	int ItemCount;

	FInventoryItemData()
		: InventoryItem(nullptr), ItemCount(0)
	{
	}
};
