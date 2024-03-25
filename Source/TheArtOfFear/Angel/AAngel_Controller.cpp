// Produced by Lucky 13 (Team 13) for module GDEV60033, Staffordshire University.


#include "AAngel_Controller.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


AAAngel_Controller::AAAngel_Controller()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AAAngel_Controller::BeginPlay()
{
	Super::BeginPlay();


	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}


void AAAngel_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AAAngel_Controller::InitializeBT);
}

void AAAngel_Controller::InitializeBT()
{
	BehaviorTreeComponent->StartLogic();
	UBehaviorTree* BT = BehaviorTreeComponent->GetCurrentTree();

	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
		//Blackboard->SetValueAsObject("PlayerCharacter", UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	}
}
