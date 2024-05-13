// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheArtOfFear/DigitalCamera/APhotoGallery.h"
#include "TheArtOfFear/UI/Menus/APauseMenuContainer.h"

#include "APlayerController.generated.h"

class UAPhotoGallery;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseMenuVisibilityChangedDelegate, bool, bIsVisible);

/**
 * 
 */
UCLASS()
class THEARTOFFEAR_API AAPlayerController : public APlayerController
{
	GENERATED_BODY()

	// OVERRIDES
protected:
	virtual void BeginPlay() override;

	// INTERFACE
public:
	void RequestTogglePause();

	UFUNCTION(BlueprintCallable, Category="APlayerController|Interface")
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable, Category="APlayerController|Interface")
	void HidePauseMenu();

	// UAPhotoGallery* GetPhotoGallery();
	
protected:
	bool TryCreatePauseMenuContainer();

	// bool TryCreatePhotoGallery();

	UPROPERTY(BlueprintAssignable)
	FPauseMenuVisibilityChangedDelegate OnPauseMenuVisibilityChanged;

	// PARAMS
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerController|Params")
	TSubclassOf<UUserWidget> PauseMenuContainerClass = UAPauseMenuContainer::StaticClass();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerController|Params")
	TSubclassOf<UAPhotoGallery> PhotoGalleryClass = UAPhotoGallery::StaticClass();
	
	// INTERNAL
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="APlayerController|Internal")
	TWeakObjectPtr<UUserWidget> PauseMenuContainer = nullptr;
	
	// UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="APlayerController|Internal")
	// TWeakObjectPtr<UAPhotoGallery> PhotoGallery = nullptr;
	
};
