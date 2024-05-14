// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheArtOfFear/UI/Menus/APauseMenuContainer.h"

#include "APlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseMenuVisibilityChangedDelegate, bool, bIsVisible);

/**
 * 
 */
UCLASS()
class THEARTOFFEAR_API AAPlayerController : public APlayerController
{
	GENERATED_BODY()

	// INTERFACE
public:
	void RequestTogglePause();

	UFUNCTION(BlueprintCallable, Category="APlayerController|Interface")
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable, Category="APlayerController|Interface")
	void HidePauseMenu();

	UFUNCTION(BlueprintCallable, Category="APlayerController|Interface")
	TArray<UTextureRenderTarget2D*>& GetPhotos();

	UFUNCTION(BlueprintCallable, Category="APlayerController|Interface")
	void AddPhoto(UTextureRenderTarget2D* InPhoto);
	
protected:
	bool TryCreatePauseMenuContainer();

	UPROPERTY(BlueprintAssignable)
	FPauseMenuVisibilityChangedDelegate OnPauseMenuVisibilityChanged;

	// PARAMS
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerController|Params")
	TSubclassOf<UUserWidget> PauseMenuContainerClass = UAPauseMenuContainer::StaticClass();
	
	// INTERNAL
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="APlayerController|Internal")
	TWeakObjectPtr<UUserWidget> PauseMenuContainer = nullptr;

	TArray<UTextureRenderTarget2D*> RenderTargetGallery;
	
};
