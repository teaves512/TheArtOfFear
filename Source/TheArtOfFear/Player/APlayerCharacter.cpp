// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "APlayerCharacter.h"

#include "APlayerController.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/AInputConfigData.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAPlayerCharacter::AAPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false; // TODO: This must be enable when Tick is in use.

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
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
	PEI->BindAction(InputActions.Get()->InputJump.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Jump);
	PEI->BindAction(InputActions.Get()->InputCrouch.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Crouch);
	PEI->BindAction(InputActions.Get()->InputToggleCamera.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_ToggleCamera);
	PEI->BindAction(InputActions.Get()->InputTakePhoto.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_TakePhoto);
	PEI->BindAction(InputActions.Get()->InputInteract.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Interact);
	PEI->BindAction(InputActions.Get()->InputPause.LoadSynchronous(), ETriggerEvent::Started, this, &AAPlayerCharacter::OnInput_Pause);
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
	//If Player is crouching don't sprint
	if (IsCrouching == false) {
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
		IsSprinting = true;
		GetWorldTimerManager().SetTimer(StaminaTimer, this, &AAPlayerCharacter::StaminaDecrease, 0.1f, true);
	}
	
}

void AAPlayerCharacter::OnInput_EndSprint(const FInputActionValue& Value)
{
	if (IsCrouching == false) {
		GetCharacterMovement()->MaxWalkSpeed = InitialMaxWalkSpeed;
	}
	IsSprinting = false;
	GetWorldTimerManager().SetTimer(StaminaTimer, this, &AAPlayerCharacter::StaminaIncrease, 0.05f, true, 2.f);
}

void AAPlayerCharacter::StaminaDecrease()
{
	//Decrease Stamina by 1, if Stamina is less than or equal to 0, set Stamina to 0 and trigger EndSprint
	StaminaCurrent--;
	if (StaminaCurrent <= 0) {
		StaminaCurrent = 0;
		OnInput_EndSprint(true);
	}
}

void AAPlayerCharacter::StaminaIncrease()
{
	//Increase Stamina by 1, if Stamina is greater than or equal to StaminaMax, set Stamina to StaminaMax and clear the timer
	StaminaCurrent++;
	if (StaminaCurrent >= StaminaMax) {
		StaminaCurrent = StaminaMax;
		GetWorldTimerManager().ClearTimer(StaminaTimer);
	}
}

void AAPlayerCharacter::OnInput_Jump(const FInputActionValue& Value)
{
	if (IsCrouching == false) {
		Jump();
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

bool AAPlayerCharacter::TryFindPlayerController()
{
	PlayerController = Cast<AAPlayerController>(GetController());
	return PlayerController.IsValid();
}
