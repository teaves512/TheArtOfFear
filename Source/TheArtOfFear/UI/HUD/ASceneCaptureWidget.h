// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ASceneCaptureWidget.generated.h"

class UTextureRenderTarget2D;

/**
 * Widget used to display scene captures created when the digital camera takes a photo.
 */
UCLASS()
class THEARTOFFEAR_API UASceneCaptureWidget : public UUserWidget
{
	GENERATED_BODY()

	// INTERFACE
public:
	void SetPhotoRender(UTextureRenderTarget2D* InPhotoRender);

	// INTERNAL
protected:
	UPROPERTY(BlueprintReadOnly, Category="UASceneCaptureWidget|Internal")
	UTextureRenderTarget2D* PhotoRender = nullptr;
	
};
