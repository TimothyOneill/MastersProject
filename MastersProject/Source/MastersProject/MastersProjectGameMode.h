// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include <unordered_set>
#include "MastersProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSPROJECT_API AMastersProjectGameMode : public AGameMode
{
    GENERATED_BODY()
public:

    AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer);

    //Transitions to Waiting to Start.
    virtual void StartPlay() override;
    virtual void HandleMatchHasStarted();
    virtual void HandleMatchHasEnded();

    void RestartGameTimer();
    void StopGameTimer();
    void ChangeTestScenario();
    void GenerateTestOrder();

protected:

    FTimerHandle GameTimerHandle;
    std::unordered_set<int> TestOrder;
    float GameTimer = 5.0f;
};
