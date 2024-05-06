// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.

#include "IAHealthComponentInterface.h"

UAHealthComponent* IIAHealthComponentInterface::GetHealthComponent_Implementation()
{
	ensureMsgf(false, TEXT("IIAHealthComponentInterface::GetHealthComponent failed. Method must be overriden in child class."));
	return nullptr;
}
