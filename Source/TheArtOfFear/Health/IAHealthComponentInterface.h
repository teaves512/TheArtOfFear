// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "IAHealthComponentInterface.generated.h"

class UAHealthComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIAHealthComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEARTOFFEAR_API IIAHealthComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="AIHealthComponentInterface")
	UAHealthComponent* GetHealthComponent();
	virtual UAHealthComponent* GetHealthComponent_Implementation();
	
};
