// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:

	const TArray<AActor*>& GetPatrolPoints();

	UPROPERTY(EditAnywhere, Category = "Patrol")
	TArray<AActor*> PatrolPoints;
	
};
