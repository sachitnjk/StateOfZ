// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyEnumTypes.generated.h"

UENUM(BlueprintType)
enum class EEnemyAiState : uint8
{
	Default	= 0					UMETA(DisplayName = "Default"),
	Dead = 1					UMETA(DisplayName = "Dead"),
	Chase = 2					UMETA(DisplayName = "Chase"),
	Attack = 3					UMETA(DisplayName = "Attack"),
	InvestigateLastSeen = 4		UMETA(DisplayName = "Investigate Last Seen"),
	InvestigateSound = 5		UMETA(DisplayName = "Investigate Sound"),
};
