// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "ACameraCaptureComponent.h"

#include "APhotoGallery.h"
#include "APhotogradingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "TheArtOfFear/Player/APlayerCharacter.h"
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

	PhotoSetupDelegate.Broadcast(0);

	UTextureRenderTarget2D* RT = UKismetRenderingLibrary::CreateRenderTarget2D(this, RenderTargetWidth, RenderTargetHeight);
	UASceneCaptureWidget* SceneCaptureWidget = CreateWidget<UASceneCaptureWidget>(
		PlayerController.Get(),
		SceneCaptureWidgetClass.LoadSynchronous(),
		TEXT("SceneCaptureWidget")
	);

	APlayerController* PC = Cast<APlayerController>(PlayerController.Get());
	const int32 Score = PhotogradingComponent->GradePhoto_BP(GetEyeLocation(), PC);

	if (SavedRTCount < 250)
	{
		TextureTarget = RT;
		CaptureScene();
		SceneCaptureWidget->SetPhotoRender(RT);

		if (CurrentSceneCaptureWidgets.IsValid())
		{
			CurrentSceneCaptureWidgets->RemoveFromParent();
		}
		CurrentSceneCaptureWidgets = SceneCaptureWidget;
		CurrentSceneCaptureWidgets->AddToViewport();

		if (Score > 0)
		{
			const FAPhotoGrade PhotoGrade = FAPhotoGrade(Score, RT);
			PlayerController->AddPhoto(PhotoGrade);
		}

		++SavedRTCount;
	}

	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UADigitalCameraComponent::FinishCameraCooldown, PhotoCooldownTime, false);
	PhotoTakenDelegate.Broadcast(Score);
}

void UADigitalCameraComponent::SetPhotogradingComponent(UAPhotogradingComponent* InPhotogradingComp)
{
	PhotogradingComponent = InPhotogradingComp;
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

	if (!ensureMsgf(PhotogradingComponent.IsValid(), TEXT("UADigitalCameraComponent::EnsureCanTakePhoto failed. PhotogradingComponent is invalid.")))
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

FVector UADigitalCameraComponent::GetEyeLocation() const
{
	const AAPlayerCharacter* Character = Cast<AAPlayerCharacter>(GetOwner());
	return Character->GetCameraLocation();
}
