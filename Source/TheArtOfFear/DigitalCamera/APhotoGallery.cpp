// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APhotoGallery.h"

void UAPhotoGallery::AddPhotoRender(UTextureRenderTarget2D* InPhotoRender)
{
	if (ensureMsgf(InPhotoRender, TEXT("UAPhotoGallery::AddPhotoRender failed. InPhotoRender was invalid.")))
	{
		PhotoRenders.Emplace(InPhotoRender);
		OnPhotoRenderAdded(InPhotoRender);
	}
}
