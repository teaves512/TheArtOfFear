// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"

#include "APhotoGrade.generated.h"

USTRUCT(BlueprintType)
struct FAPhotoGrade
{
	GENERATED_BODY()

	FAPhotoGrade()
	{
		Score = 0;
		RenderTarget = nullptr;
	}
	FAPhotoGrade(int32 InScore, UTextureRenderTarget2D* InRenderTarget)
	{
		Score = InScore;
		RenderTarget = InRenderTarget;
	}
	~FAPhotoGrade() {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* RenderTarget = nullptr;
	
};
