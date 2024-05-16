// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "ACameraCaptureComponent.h"

#include "APhotoGallery.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "TheArtOfFear/UI/HUD/ASceneCaptureWidget.h"

UADigitalCameraComponent::UADigitalCameraComponent()
{
	bCaptureEveryFrame = false;
	bCaptureOnMovement = false;
	bAlwaysPersistRenderingState = true;
}

void UADigitalCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	TryFindPlayerController();
}

void UADigitalCameraComponent::TakePhoto()
{
	if (!EnsureCanTakePhoto())
	{
		return;
	}

	// If the cooldown has not complete, don't take a photo.
	if (CooldownTimerHandle.IsValid())
	{
		return;
	}

	PhotoSetupDelegate.Broadcast();

	UTextureRenderTarget2D* RT = UKismetRenderingLibrary::CreateRenderTarget2D(this, RenderTargetWidth, RenderTargetHeight);
	UASceneCaptureWidget* SceneCaptureWidget = CreateWidget<UASceneCaptureWidget>(
		PlayerController.Get(),
		SceneCaptureWidgetClass.LoadSynchronous(),
		TEXT("SceneCaptureWidget")
	);

	TextureTarget = RT;
	CaptureScene();
	SceneCaptureWidget->SetPhotoRender(RT);
	SceneCaptureWidget->AddToViewport();

	if (CurrentSceneCaptureWidgets.IsValid())
	{
		CurrentSceneCaptureWidgets->RemoveFromParent();
	}
	CurrentSceneCaptureWidgets = SceneCaptureWidget;

	const FAPhotoGrade PhotoGrade = FAPhotoGrade(0, RT);
	PlayerController->AddPhoto(PhotoGrade);

	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UADigitalCameraComponent::FinishCameraCooldown, PhotoCooldownTime, false);
	PhotoTakenDelegate.Broadcast();
}

void UADigitalCameraComponent::TryFindPlayerController()
{
	// TODO: Should be taken from the GameMode.
	PlayerController = Cast<AAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ensureMsgf(PlayerController.IsValid(), TEXT("UADigitalCameraComponent::TryFindPlayerController failed."));
}

bool UADigitalCameraComponent::EnsureCanTakePhoto() const
{
	if (!ensureMsgf(PlayerController.IsValid(), TEXT("UADigitalCameraComponent::EnsureCanTakePhoto failed. PlayerController is invalid.")))
	{
		return false;
	}

	if (!ensureMsgf(SceneCaptureWidgetClass.LoadSynchronous() != UASceneCaptureWidget::StaticClass(), TEXT("UADigitalCameraComponent::EnsureCanTakePhoto failed. SceneCaptureWidgetClass has not been set.")))
	{
		return false;
	}

	return true;
}

void UADigitalCameraComponent::FinishCameraCooldown()
{
	CooldownTimerHandle.Invalidate();
	
	CameraCooldownDelegate.Broadcast();
}
