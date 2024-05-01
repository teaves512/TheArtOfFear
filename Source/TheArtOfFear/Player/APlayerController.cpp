// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APlayerController.h"
#include "TheArtOfFear/UI/Menus/APauseMenuContainer.h"

void AAPlayerController::RequestTogglePause()
{
	// TODO: Pause game through game mode.

	if (PauseMenuContainer.IsValid() == false)
	{
		if (!ensureMsgf(TryCreatePauseMenuContainer(), TEXT("AAPlayerController::RequestPause failed to find or instantiate PauseMenuContainer")))
		{
			return;
		}
	}

	if (PauseMenuContainer->IsInViewport())
	{
		HidePauseMenu();
	}
	else
	{
		ShowPauseMenu();
	}
}

void AAPlayerController::ShowPauseMenu()
{
	PauseMenuContainer->AddToViewport();

	OnPauseMenuVisibilityChanged.Broadcast(true);
}

void AAPlayerController::HidePauseMenu()
{
	PauseMenuContainer->RemoveFromParent();
	
	OnPauseMenuVisibilityChanged.Broadcast(false);
}

bool AAPlayerController::TryCreatePauseMenuContainer()
{
	if (!ensureMsgf(PauseMenuContainerClass != UUserWidget::StaticClass(), TEXT("AAPlayerController::TryCreatePauseMenuContainer failed. PauseMenuContainerClass has not been set.")))
	{
		return false;
	}
	
	PauseMenuContainer = CreateWidget<UUserWidget>(this, PauseMenuContainerClass);
	return PauseMenuContainer.IsValid();
}
