// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.


#include "BaseEnemyCharacter.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set to true to allow enemy to tick
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
