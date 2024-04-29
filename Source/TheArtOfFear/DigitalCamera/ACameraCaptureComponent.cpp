// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "ACameraCaptureComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "TheArtOfFear/UI/HUD/ASceneCaptureWidget.h"

UADigitalCameraComponent::UADigitalCameraComponent()
{
	bCaptureEveryFrame = false;
	bCaptureOnMovement = false;
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
	
	UTextureRenderTarget2D* RT = UKismetRenderingLibrary::CreateRenderTarget2D(this, RenderTargetWidth, RenderTargetHeight);
	UASceneCaptureWidget* SceneCaptureWidget = CreateWidget<UASceneCaptureWidget>(
		PlayerController.Get(),
		SceneCaptureWidgetClass.LoadSynchronous(),
		TEXT("SceneCaptureWidget")
	);
	
	CaptureScene();
	SceneCaptureWidget->AddToViewport();

	PhotoTakenDelegate.Broadcast();
}

void UADigitalCameraComponent::TryFindPlayerController()
{
	// TODO: Should be taken from the GameMode.
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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
