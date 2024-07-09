#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class AStateOfZCharacter;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class STATEOFZ_API IInteractable
{
	GENERATED_BODY()

public:
	//pure virtual functions
	virtual void OnHover() = 0;
	virtual void OnHoverDisable() = 0;
	virtual void OnInteractStart(AStateOfZCharacter* PlayerChar) = 0;
	virtual void OnInteractOngoing() = 0;
	virtual  void OnInteractStop() = 0;
};
