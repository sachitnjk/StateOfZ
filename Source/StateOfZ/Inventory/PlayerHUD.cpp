#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUD::HandleOnHoverChanged(bool IsHoverActive)
{
	SetSearchHoverUI(IsHoverActive);
}

void UPlayerHUD::HandleOnSearchingChanged(bool IsSearchingActive)
{
	SetOnSearchingUI(IsSearchingActive);
}


void UPlayerHUD::SetSearchHoverUI(bool IsHoverActive)
{
	if(HoverSearchText)
	{
		HoverSearchText->SetVisibility(IsHoverActive ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UPlayerHUD::SetOnSearchingUI(bool IsSearchingActive)
{
	if(SearchingText)
	{
		SearchingText->SetVisibility(IsSearchingActive ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

