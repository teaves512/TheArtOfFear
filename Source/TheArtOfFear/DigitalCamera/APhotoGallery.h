// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "TheArtOfFear/UI/HUD/ASceneCaptureWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"

#include "APhotoGallery.generated.h"

class AAPlayerController;
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
protected:
	UFUNCTION(BlueprintCallable, Category="UAPhotoGallery|Interface")
	bool TryFindPlayerController();

	// PARAMS
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UAPhotoGallery|Params")
	TSubclassOf<UASceneCaptureWidget> SceneCaptureWidgetClass;

	// INTERNAL
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> WrapBox_Gallery = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="UAPhotoGallery|Internal")
	TWeakObjectPtr<AAPlayerController> PlayerController = nullptr;
	
};
