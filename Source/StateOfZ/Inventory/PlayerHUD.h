#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerHUD.generated.h"

UCLASS()
class STATEOFZ_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetSearchHoverUI(bool IsHoverActive);
	void SetOnSearchingUI(bool IsSearchingActive);

	UFUNCTION()
	void HandleOnHoverChanged(bool IsHoverActive);
	UFUNCTION()
	void HandleOnSearchingChanged(bool IsSearchingActive);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* HoverSearchText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* SearchingText;
	
};
