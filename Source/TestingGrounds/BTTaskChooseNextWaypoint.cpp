// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskChooseNextWaypoint.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UBTTaskChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* ptReqBlackboard = OwnerComp.GetBlackboardComponent();

	// Get patrol points.
	AAIController* ptAIController = OwnerComp.GetAIOwner();
	if (!ensure(ptAIController)) { return EBTNodeResult::Failed; }
	APawn* ptReqPawn = ptAIController->GetPawn();
	if (!ensure(ptReqPawn)) { return EBTNodeResult::Failed; }
	UPatrolRoute* ptPatrolRouteComponent = Cast<UPatrolRoute>(ptReqPawn->GetComponentByClass(UPatrolRoute::StaticClass()));
	if (!ensure(ptPatrolRouteComponent)) { return EBTNodeResult::Failed; }

	const TArray<AActor*>& patrolPoints = ptPatrolRouteComponent->GetPatrolPoints();
	if (patrolPoints.Num() <= 0) { return EBTNodeResult::Failed; }
		 
	// Set next waypoint.
	int32 reqIndexValue = ptReqBlackboard->GetValueAsInt(IndexBBKeySelector.SelectedKeyName);
	AActor* ptNextWaypoint = patrolPoints[reqIndexValue];
	ptReqBlackboard->SetValueAsObject(WaypointBBKeySelector.SelectedKeyName, ptNextWaypoint);

	// Cycle waypoint index.
	int32 nwIndexValue = (reqIndexValue + 1) % patrolPoints.Num();
	ptReqBlackboard->SetValueAsInt(IndexBBKeySelector.SelectedKeyName, nwIndexValue);

	return EBTNodeResult::Succeeded;
}