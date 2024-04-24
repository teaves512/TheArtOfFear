// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "AInputConfigData.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class THEARTOFFEAR_API UAInputConfigData : public UDataAsset
{
	GENERATED_BODY()

	// INPUT ACTIONS
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AInputConfigData")
	TSoftObjectPtr<UInputAction> InputMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AInputConfigData")
	TSoftObjectPtr<UInputAction> InputLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AInputConfigData")
	TSoftObjectPtr<UInputAction> InputSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AInputConfigData")
	TSoftObjectPtr<UInputAction> InputJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AInputConfigData")
	TSoftObjectPtr<UInputAction> InputTakePhoto = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AInputConfigData")
	TSoftObjectPtr<UInputAction> InputPause = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AInputConfigData")
	TSoftObjectPtr<UInputAction> InputInteract = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AInputConfigData")
	TSoftObjectPtr<UInputAction> InputCrouch = nullptr;
};
