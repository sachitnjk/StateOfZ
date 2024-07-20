#pragma once

#include "ItemSlotType.generated.h"

UENUM(BlueprintType)
enum class EItemSlotType : uint8
{
	PrimaryMelee UMETA(DisplayName = "Primary Melee"),
	SecondaryMelee UMETA(DisplayName = "Secondary Melee"),
	PrimaryRanged UMETA(DislayName = "Primary Ranged"),
	SecondaryRanged UMETA(DisplayName = "Secondary Ranged"),
	General UMETA(DisplayName = "General")
};
