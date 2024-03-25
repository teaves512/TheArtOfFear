// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.


#include "AAngel_Character.h"

// Sets default values
AAAngel_Character::AAAngel_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAAngel_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAngel_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAAngel_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

