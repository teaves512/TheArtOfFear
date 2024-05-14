// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APhotoGallery.h"

#include "Kismet/GameplayStatics.h"
#include "TheArtOfFear/Player/APlayerController.h"

bool UAPhotoGallery::TryFindPlayerController()
{
	// TODO: Should be taken from the GameMode.
	PlayerController = Cast<AAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (ensureMsgf(PlayerController.IsValid(), TEXT("UADigitalCameraComponent::TryFindPlayerController failed.")))
	{
		return true;
	}

	return false;
}
