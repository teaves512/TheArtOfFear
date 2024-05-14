// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APlayerController.h"
#include "TheArtOfFear/DigitalCamera/APhotoGallery.h"
#include "TheArtOfFear/UI/Menus/APauseMenuContainer.h"

void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// if (TryCreatePhotoGallery())
	// {
	// 	PhotoGallery->AddToViewport();
	// }
}

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

// UAPhotoGallery* AAPlayerController::GetPhotoGallery()
// {
// 	if (ensureMsgf(PhotoGallery.IsValid(), TEXT("AAPlayerController::GetPhotoGallery ")))
// 	{
// 		return PhotoGallery.Get();
// 	}
//
// 	return nullptr;
// }

bool AAPlayerController::TryCreatePauseMenuContainer()
{
	if (!ensureMsgf(PauseMenuContainerClass != UAPauseMenuContainer::StaticClass(), TEXT("AAPlayerController::TryCreatePauseMenuContainer failed. PauseMenuContainerClass has not been set.")))
	{
		return false;
	}
	
	PauseMenuContainer = CreateWidget<UUserWidget>(this, PauseMenuContainerClass);
	return PauseMenuContainer.IsValid();
}

// bool AAPlayerController::TryCreatePhotoGallery()
// {
// 	if (!ensureMsgf(PhotoGalleryClass != UAPhotoGallery::StaticClass(), TEXT("AAPlayerController::TryCreatePhotoGallery failed. PhotoGalleryClass has not been set.")))
// 	{
// 		return false;
// 	}
//
// 	PhotoGallery = CreateWidget<UUserWidget>(this, PhotoGalleryClass);
// 	return PhotoGallery.IsValid();
// }
