// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "APhotoGallery.h"
#include "Components/SceneCaptureComponent2D.h"
#include "TheArtOfFear/Player/APlayerController.h"
#include "TheArtOfFear/UI/HUD/ASceneCaptureWidget.h"

#include "ACameraCaptureComponent.generated.h"

class UASceneCaptureWidget;
class UAPhotoGallery;
class UTextureRenderTarget2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPhotoTakenDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCameraCooldownDelegate);

/**
 * Uses scene capture to export screenshots of the viewport to a render texture.
 * Should only be attached to an AAPlayerCharacter.
 */
UCLASS()
class THEARTOFFEAR_API UADigitalCameraComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()

	// OVERRIDES
protected:
	UADigitalCameraComponent();
	virtual void BeginPlay() override;

	// INTERFACE
public:
	/** Captures the scene view and applies the viewport to the specified render texture. Broadcasts OnCameraCaptures. */
	UFUNCTION(BlueprintCallable, Category="ADigitalCameraComponent|Interface")
	void TakePhoto();

	/** Broadcast just before the screen capture is taken. */
	UPROPERTY(BlueprintAssignable, Category="ADigitalCameraComponent|Interface")
	FPhotoTakenDelegate PhotoSetupDelegate;
	
	/** Broadcast when the camera captures the scene. */
	UPROPERTY(BlueprintAssignable, Category="ADigitalCameraComponent|Interface")
	FPhotoTakenDelegate PhotoTakenDelegate;

	/** Broadcast when the camera cooldown is complete. */
	UPROPERTY(BlueprintAssignable, Category="ADigitalCameraComponent|Interface")
	FCameraCooldownDelegate CameraCooldownDelegate;

protected:
	/** Find the PlayerController that owns the pawn that this component is attached to. */
	void TryFindPlayerController();

	/** Returns true if can take photo, false if not. */
	bool EnsureCanTakePhoto() const;

	/** Broadcasts CameraCooldownDelegate. */
	void FinishCameraCooldown();

	// PARAMS
protected:
	/** The width all render targets declared by any scene captures from this component. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ADigitalCameraComponent|Params")
	int32 RenderTargetWidth = 512;

	/** The height all render targets declared by any scene captures from this component. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ADigitalCameraComponent|Params")
	int32 RenderTargetHeight = 288;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ADigitalCameraComponent|Params")
	TSoftClassPtr<UASceneCaptureWidget> SceneCaptureWidgetClass = UASceneCaptureWidget::StaticClass();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ADigitalCameraComponent|Params")
	TSoftClassPtr<UAPhotoGallery> PhotoGalleryWidgetClass = UAPhotoGallery::StaticClass();
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ADigitalCameraComponent|Params")
	float PhotoCooldownTime = 1.0f;

	// INTERNAL
private:
	/** The player controller that owns the pawn that this component is attached to. */
	TWeakObjectPtr<AAPlayerController> PlayerController = nullptr;
	
	FTimerHandle CooldownTimerHandle;

	TWeakObjectPtr<UASceneCaptureWidget> CurrentSceneCaptureWidgets = nullptr;
	
};
