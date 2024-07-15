#pragma once

#include "CoreMinimal.h"
#include "StateOfZ/AI/BaseAiController.h"
#include "ChaserAiController.generated.h"

UCLASS()
class STATEOFZ_API AChaserAiController : public ABaseAiController
{
	GENERATED_BODY()

protected:
	virtual void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
	virtual void PerceptionForget(AActor* Actor) override;

	FName BBK_InvestigationPosition = FName("InvestigationPosition");
	FName BBK_NewSoundRegistered = FName("NewSoundRegistered");
};
