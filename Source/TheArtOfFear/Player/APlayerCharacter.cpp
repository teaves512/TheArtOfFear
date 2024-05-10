// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APlayerCharacter.h"

#include "TheArtOfFear/DigitalCamera/ACameraCaptureComponent.h"
#include "APlayerController.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/AInputConfigData.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TheArtOfFear/Health/AHealthComponent.h"

AAPlayerCharacter::AAPlayerCharacter()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	DigitalCameraComp = CreateDefaultSubobject<UADigitalCameraComponent>(TEXT("DigitalCameraComp"));
	DigitalCameraComp->SetupAttachment(CameraComp);

	HealthComponent = CreateDefaultSubobject<UAHealthComponent>(TEXT("HealthComponent"));
}
void AAPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitialMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Get the player controller.
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);

	// Get the enhanced input component.
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	InputActions.LoadSynchronous();

	// Bind the actions.
	PEI->BindAction(InputActions.Get()->InputMove.LoadSynchronous(), ETriggerEvent::Triggered, this, &AAPlayerCharacter::OnInput_Move);
	PEI->BindAction(InputActions.Get()->InputLook.LoadSynchronous(), ETriggerEvent::Triggered, this, &AAPlayerCharacter::OnInput_Look);
	PEI->BindAction(InputActions.Get()->InputSprint.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_StartSprint);
	PEI->BindAction(InputActions.Get()->InputSprint.LoadSynchronous(), ETriggerEvent::Completed, this, &AAPlayerCharacter::OnInput_EndSprint);
	PEI->BindAction(InputActions.Get()->InputSprint.LoadSynchronous(), ETriggerEvent::Canceled, this, &AAPlayerCharacter::OnInput_EndSprint);
	PEI->BindAction(InputActions.Get()->InputTakePhoto.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_TakePhoto);
	PEI->BindAction(InputActions.Get()->InputInteract.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Interact);
	PEI->BindAction(InputActions.Get()->InputPause.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Pause);
	PEI->BindAction(InputActions.Get()->InputFlashlight.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Flashlight);
	PEI->BindAction(InputActions.Get()->InputHoldCamera.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_StartHoldCamera);
	PEI->BindAction(InputActions.Get()->InputHoldCamera.LoadSynchronous(), ETriggerEvent::Completed, this, &AAPlayerCharacter::OnInput_EndHoldCamera);
	PEI->BindAction(InputActions.Get()->InputHoldCamera.LoadSynchronous(), ETriggerEvent::Canceled, this, &AAPlayerCharacter::OnInput_EndHoldCamera);
}

void AAPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Tick is currently disabled. Enable in the constructor.
}

void AAPlayerCharacter::OnInput_Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
 
		// Forward/Backward direction.
		if (MoveValue.Y != 0.f)
		{
			// Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
 
			AddMovementInput(Direction, MoveValue.Y);
		}
 
		// Right/Left direction.
		if (MoveValue.X != 0.f)
		{
			// Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
 
			AddMovementInput(Direction, MoveValue.X);
		}

		PlayerMakeNoise();
	}
}

void AAPlayerCharacter::OnInput_Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();

		// Yaw input turns the whole character.
		if (LookValue.X != 0.0f)
		{
			AddControllerYawInput(LookValue.X);
		}

		// Pitch input turns the characters 'head' (the CameraComp).
		if (LookValue.Y != 0.0f)
		{
			FRotator CameraRot = CameraComp->GetRelativeRotation();
			CameraRot.Pitch = FMath::Clamp(CameraRot.Pitch + LookValue.Y, -MaxLookAngle, MaxLookAngle);
			
			CameraComp->SetRelativeRotation(CameraRot);
		}
	}
}

void AAPlayerCharacter::OnInput_StartSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void AAPlayerCharacter::OnInput_EndSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = InitialMaxWalkSpeed;
}

void AAPlayerCharacter::OnInput_TakePhoto(const FInputActionValue& Value)
{
	if (bHoldingCamera)
	{
		DigitalCameraComp->TakePhoto();
	}
}

void AAPlayerCharacter::OnInput_Interact(const FInputActionValue& Value)
{
}

void AAPlayerCharacter::OnInput_Pause(const FInputActionValue& Value)
{
	if (PlayerController.IsValid() == false)
	{
		if (!ensureMsgf(TryFindPlayerController(), TEXT("AAPlayerCharacter::OnInput_Interact failed because PlayerController was invalid and failed to instantiate.")))
		{
			return;
		}
	}

	PlayerController->RequestTogglePause();
}

void AAPlayerCharacter::OnInput_Flashlight(const FInputActionValue& Value)
{
	ToggleFlashlight();
}

void AAPlayerCharacter::OnInput_StartHoldCamera(const FInputActionValue& Value)
{
	bHoldingCamera = true;
	
	StartHoldCamera_BP();
}

void AAPlayerCharacter::OnInput_EndHoldCamera(const FInputActionValue& Value)
{
	bHoldingCamera = false;
	
	EndHoldCamera_BP();
}

bool AAPlayerCharacter::TryFindPlayerController()
{
	PlayerController = Cast<AAPlayerController>(GetController());
	return PlayerController.IsValid();
}

UAHealthComponent* AAPlayerCharacter::GetHealthComponent_Implementation()
{
	return HealthComponent.Get();
}
