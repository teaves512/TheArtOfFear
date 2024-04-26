// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/Character.h"

#include "APlayerCharacter.generated.h"

class UADigitalCameraComponent;
class UAInputConfigData;
class UCameraComponent;
class UInputMappingContext;
struct FInputActionValue;

/**
 * The base class for The Art of Fear's custom player character.
 */
UCLASS()
class THEARTOFFEAR_API AAPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	friend class AAPlayerController;

	// OVERRIDES
protected:
	AAPlayerCharacter();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	// INTERFACE
protected:
	void OnInput_Move(const FInputActionValue& Value);
	void OnInput_Look(const FInputActionValue& Value);
	void OnInput_StartSprint(const FInputActionValue& Value);
	void OnInput_EndSprint(const FInputActionValue& Value);
	void OnInput_Jump(const FInputActionValue& Value);
	void OnInput_TakePhoto(const FInputActionValue& Value);
	void OnInput_Interact(const FInputActionValue& Value);
	void OnInput_Pause(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerMakeNoise();

	bool TryFindPlayerController();

	// PARAMS
protected:
	/** The input mapping context used by this player character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerCharacter|EnhancedInput")
	TSoftObjectPtr<UInputMappingContext> InputMapping = nullptr;

	/** The data asset that defines which input actions are available this player character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerCharacter|EnhancedInput")
	TSoftObjectPtr<UAInputConfigData> InputActions = nullptr;

	/** The maximum angle the pitch of the camera can be, both above and below horizontal. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerCharacter|Camera")
	float MaxLookAngle = 80.0f;

	/** Movement speed, in cm/s, when the player character is sprinting. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="APlayerCharacter|Movement")
	float MaxSprintSpeed = 1000.0f;

	// COMPONENTS
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="APlayerCharacter|Components")
	TObjectPtr<UCameraComponent> CameraComp = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="APlayerCharacter|Components")
	TObjectPtr<UADigitalCameraComponent> DigitalCameraComp = nullptr;

	// INTERNAL
protected:
	TWeakObjectPtr<AAPlayerController> PlayerController = nullptr;
	
private:
	float InitialMaxWalkSpeed = 0.0f;

};
