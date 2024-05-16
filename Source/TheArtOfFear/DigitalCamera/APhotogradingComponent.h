// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "APhotogradingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class THEARTOFFEAR_API UAPhotogradingComponent : public UActorComponent
{
	GENERATED_BODY()

	// INTERFACE
public:
	UFUNCTION(BlueprintImplementableEvent, Category="UAPhotogradingComponent")
	int32 GradePhoto_BP(FVector EyeLocation, APlayerController* PlayerController);
	
};
