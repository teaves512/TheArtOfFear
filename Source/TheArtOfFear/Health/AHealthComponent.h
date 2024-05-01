// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAHealthChangedDelegate, const float, OldValue, const float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAAliveChangedDelegate, const bool, bWasAlive, const bool, bIsAlive);

/**
 * Component for managing the health of it's owner.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEARTOFFEAR_API UAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// OVERRIDES
protected:
	UAHealthComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// INTERFACE
public:
	UFUNCTION(BlueprintGetter, Category="AHealthComponent")
	float GetHealth() const;

	UFUNCTION(BlueprintGetter, Category="AHealthComponent")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintGetter, Category="AHealthComponent")
	bool GetAlive() const;

protected:
	/** Sets health and checks for death. */
	UFUNCTION(BlueprintCallable, Category="AHealthComponent", meta=(AutoCreateRefTerm="NewHealth"))
	void SetHealth(const float& NewHealth);

	UFUNCTION(BlueprintCallable, Category="AHealthComponent", meta=(AutoCreateRefTerm="NewHealth"))
	void SetAlive(const bool bNewAlive);
	
	/** Regenerates a specific amount of health over time. */
	void RegenHealthOverTime(const float& DeltaTime);

	/** Callback for when damage is received. */
	UFUNCTION()
	void DamageReceivedCallback(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/** Sets off a timer to enable the component's tick function, allowing for health to regenerate. */
	void InvokeHealthRegen();

	/** Called when the owner of this component dies. */
	void Death();

	/** Broadcast when the health of the owner of this component changes. */
	UPROPERTY(BlueprintAssignable, Category="AHealthComponent")
	FAHealthChangedDelegate OnHealthChanged;

	/** Broadcast when the alive state of the owner of this component changes. */
	UPROPERTY(BlueprintAssignable, Category="AHealthComponent")
	FAAliveChangedDelegate OnAliveChanged;

	// PARAMS
protected:
	/** The maximum amount of damage the owner of this component can survive. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AHealthComponent", meta=(ClampMin=0))
	float MaxHealth = 100.0f;

	/** The amount of time between receiving damage and when health starts regenerating. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AHealthComponent", meta=(ClampMin=0))
	float RegenDelay = 100.0f;

	/** The amount of health to regenerate every second. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AHealthComponent", meta=(ClampMin=0))
	float RegenRate = 10.0f;

	// INTERNAL
private:
	/** When alive, the component is active. */
	bool bAlive = true;
	
	/** The remaining amount of damage that the owner of this component can survive. */
	float Health = 0.0f;

	/** Timer handle that manages when to start regenerating health after taking damage. */
	FTimerHandle RegenDelayTimerHandle;
	
};
