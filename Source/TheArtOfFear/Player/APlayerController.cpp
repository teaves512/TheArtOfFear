// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APlayerController.h"
#include "TheArtOfFear/DigitalCamera/APhotoGallery.h"
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

TArray<FAPhotoGrade>& AAPlayerController::GetPhotos()
{
	return PhotoGallery;
}

TArray<FAPhotoGrade> AAPlayerController::GetPhotosBetweenIndex(const int32 MinIndex, const int32 MaxIndex)
{
	if (!ensureMsgf(MinIndex < 0 || MinIndex > PhotoGallery.Num() - 1, TEXT("AAPlayerController::GetPhotosBetweenIndex failed. MinIndex out of range.")))
	{
		return TArray<FAPhotoGrade>();
	}

	if (!ensureMsgf(MinIndex < 0 || MaxIndex > PhotoGallery.Num() - 1, TEXT("AAPlayerController::GetPhotosBetweenIndex failed. MinIndex out of range.")))
	{
		return TArray<FAPhotoGrade>();
	}

	if (!ensureMsgf(MinIndex > MaxIndex, TEXT("AAPlayerController::GetPhotosBetweenIndex failed. MinIndex must be <= MaxIndex.")))
	{
		return TArray<FAPhotoGrade>();
	}

	TArray<FAPhotoGrade> Photos;
	for (int32 i = MinIndex; i < MaxIndex; ++i)
	{
		Photos.Emplace(PhotoGallery[i]);
	}

	return Photos;
}

void AAPlayerController::AddPhoto(FAPhotoGrade InPhoto)
{
	if (InPhoto.Score <= 0)
	{
		return;
	}
	
	PhotoGallery.Emplace(InPhoto);
	
	if (PhotoGallery.Num() > MaxPhotoCount)
	{
		CleanupPhotoGallery();
	}
}

bool AAPlayerController::TryCreatePauseMenuContainer()
{
	if (!ensureMsgf(PauseMenuContainerClass != UAPauseMenuContainer::StaticClass(), TEXT("AAPlayerController::TryCreatePauseMenuContainer failed. PauseMenuContainerClass has not been set.")))
	{
		return false;
	}
	
	PauseMenuContainer = CreateWidget<UUserWidget>(this, PauseMenuContainerClass);
	return PauseMenuContainer.IsValid();
}

void AAPlayerController::CleanupPhotoGallery()
{
	int32 LowestScoreIndex = 0;
	for (int32 i = 1; i < PhotoGallery.Num(); ++i)
	{
		const int32 LowestScore = PhotoGallery[LowestScoreIndex].Score;
		const int32 Score = PhotoGallery[i].Score;

		if (Score < LowestScore)
		{
			LowestScoreIndex = i;
		}
	}

	PhotoGallery.RemoveAt(LowestScoreIndex);
}
