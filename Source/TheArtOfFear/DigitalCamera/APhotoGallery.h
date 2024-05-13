// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "APhotoGallery.generated.h"

class UTextureRenderTarget2D;

/**
 * Base class for WBP_PhotoGallery. Manages a number of screen captures
 * and provides the player with a method of cycling between them.
 */
UCLASS()
class THEARTOFFEAR_API UAPhotoGallery : public UUserWidget
{
	GENERATED_BODY()

	// INTERFACE
public:
	void SetPhotoRender(UTextureRenderTarget2D* InPhotoRender);

	// INTERFACE
protected:
	//...
	
};
