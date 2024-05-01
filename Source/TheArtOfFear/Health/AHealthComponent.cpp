// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "AHealthComponent.h"

UAHealthComponent::UAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	SetComponentTickEnabled(false);
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UAHealthComponent::DamageReceivedCallback);
}

void UAHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	RegenHealthOverTime(DeltaTime);
}

float UAHealthComponent::GetHealth() const
{
	return Health;
}

float UAHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

bool UAHealthComponent::GetAlive() const
{
	return bAlive;
}

void UAHealthComponent::SetHealth(const float& NewHealth)
{
	ensureMsgf(bAlive, TEXT("UAHealthComponent::SetHealth called when AHealthComponent::bAlive was false."));
	
	const float OldHealth = Health;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(OldHealth, NewHealth);

	if (FMath::IsNearlyZero(Health))
	{
		SetAlive(false);
	}
}

void UAHealthComponent::SetAlive(const bool bNewAlive)
{
	const bool bWasAlive = bAlive;
	bAlive = bNewAlive;
	OnAliveChanged.Broadcast(bWasAlive, bAlive);

	if (bAlive == false)
	{
		Death();
	}
}

void UAHealthComponent::RegenHealthOverTime(const float& DeltaTime)
{	
	const float RestoredHealth = RegenRate * DeltaTime;
	Health = FMath::Clamp(Health + RestoredHealth, 0.0f, MaxHealth);

	if (FMath::IsNearlyEqual(Health, MaxHealth))
	{
		// Stop regenerating health when health is full.
		SetComponentTickEnabled(false);
	}
}

void UAHealthComponent::DamageReceivedCallback(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	SetComponentTickEnabled(false);
	SetHealth(Health - Damage);
	InvokeHealthRegen();
}

void UAHealthComponent::InvokeHealthRegen()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenDelayTimerHandle);
	
	if (RegenDelay > 0.0f)
	{
		// Delay before enabling tick.
		FTimerDelegate RegenDelayTimerDelegate;
		RegenDelayTimerDelegate.BindUFunction(this, "SetComponentTickEnabled", true);
		GetWorld()->GetTimerManager().SetTimer(RegenDelayTimerHandle, RegenDelayTimerDelegate, RegenDelay, false);		
	}
	else
	{
		// Enable tick immediately.
		SetComponentTickEnabled(true);
	}
}

void UAHealthComponent::Death()
{
	// Stop health from regenerating.
	GetWorld()->GetTimerManager().ClearTimer(RegenDelayTimerHandle);
	SetComponentTickEnabled(false);

	// Prevent further damage.
	GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UAHealthComponent::DamageReceivedCallback);
}
