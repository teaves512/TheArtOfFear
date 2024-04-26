// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "ACameraCaptureComponent.h"

#include "Engine/Classes/Engine/TextureRenderTarget2D.h"

UADigitalCameraComponent::UADigitalCameraComponent()
{
	bCaptureEveryFrame = false;
	bCaptureOnMovement = false;
}

void UADigitalCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	RenderTargetIndexUpdatedDelegate.AddDynamic(this, &UADigitalCameraComponent::OnRenderTargetIndexUpdated);
}

void UADigitalCameraComponent::TakePhoto()
{
	UTextureRenderTarget2D* RT = RenderTargets[RenderTargetIndex].LoadSynchronous();
	if (!ensureMsgf(RT, TEXT("UADigitalCameraComponent::TakePhoto failed. RT was invalid.")))
	{
		return;
	}
	
	TextureTarget = RT;
	CaptureScene();

	// ====================================================
	// TODO: Remove the following.
	
	TextureTarget = LastPhotoRenderTarget.Get();
	CaptureScene();
	
	// ====================================================

	UpdateRenderTargetIndex();
	PhotoTakenDelegate.Broadcast();
}

void UADigitalCameraComponent::UpdateRenderTargetIndex()
{
	const int32 PreviousRenderTargetIndex = RenderTargetIndex;
	++RenderTargetIndex;

	if (RenderTargetIndex > RenderTargets.Num() - 1)
	{
		RenderTargetIndex = 0;
	}

	RenderTargetIndexUpdatedDelegate.Broadcast(PreviousRenderTargetIndex);
}

void UADigitalCameraComponent::OnRenderTargetIndexUpdated(const int32 PreviousIndex)
{
}
