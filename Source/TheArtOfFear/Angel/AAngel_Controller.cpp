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
	BehaviorTreeComponent->StartLogic();
	UBehaviorTree *BT = BehaviorTreeComponent->GetCurrentTree();

	if (IsValid(BT))
	{
		RunBehaviorTree(BehaviorTreeComponent->GetCurrentTree());
		BehaviorTreeComponent->StartTree(*BT);
	}
}


void AAAngel_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AAAngel_Controller::InitializeBT);
}

void AAAngel_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAAngel_Controller::InitializeBT()
{
	UBehaviorTree* BT = BehaviorTreeComponent->GetCurrentTree(); 

	if (IsValid(Blackboard.Get()) && IsValid(BT))
	{
		Blackboard->InitializeBlackboard(*BT->BlackboardAsset.Get()); 
		Blackboard->SetValueAsObject("PlayerCharacter", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
}
