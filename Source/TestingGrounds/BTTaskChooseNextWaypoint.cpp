// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskChooseNextWaypoint.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UBTTaskChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ptReqBlackboard = OwnerComp.GetBlackboardComponent();
	int32 reqIndexValue = ptReqBlackboard->GetValueAsInt(IndexBBKeySelector.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), reqIndexValue);

	AAIController* ptAIController = OwnerComp.GetAIOwner();
	if (!ensure(ptAIController)) { return EBTNodeResult::Failed; }
	APawn* ptReqPawn = ptAIController->GetPawn();
	if (!ensure(ptReqPawn)) { return EBTNodeResult::Failed; }
	APatrollingGuard* ptPawnAsPatrollingGuard = Cast<APatrollingGuard>(ptReqPawn);
	if (!ensure(ptPawnAsPatrollingGuard)) { return EBTNodeResult::Failed; }

	// Get patrol points.
	const TArray<AActor*>& patrolPoints = ptPawnAsPatrollingGuard->GetPatrolPoints();

	// Set next waypoint.
	AActor* ptNextWaypoint = patrolPoints[reqIndexValue];
	ptReqBlackboard->SetValueAsObject(WaypointBBKeySelector.SelectedKeyName, ptNextWaypoint);

	// Cycle waypoint index.
	int32 nwIndexValue = (reqIndexValue + 1) % patrolPoints.Num();
	ptReqBlackboard->SetValueAsInt(IndexBBKeySelector.SelectedKeyName, nwIndexValue);

	return EBTNodeResult::Succeeded;
}