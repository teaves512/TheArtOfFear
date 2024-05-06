// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "ASceneCaptureWidget.h"

void UASceneCaptureWidget::SetPhotoRender(UTextureRenderTarget2D* InPhotoRender)
{
	if (ensureMsgf(InPhotoRender, TEXT("UASceneCaptureWidget::SetPhotoRender failed. InPhotoRender was invalid.")))
	{
		PhotoRender = InPhotoRender;
	}
}
