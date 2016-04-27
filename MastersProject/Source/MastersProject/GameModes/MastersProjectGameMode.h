#pragma once
#include "GameFramework/GameMode.h"
#include <unordered_set>
#include "../Utilities/MastersProjectWorldSettings.h"
#include "../Utilities/MetricTracker.h"
#include "Interfaces/InterfaceManager.h"
#include "MastersProjectGameMode.generated.h"

/**
* MastersProjectGameMode Defines the rules for the main experiment
* Randomises Interfaces at the start of each game.
**/

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
    void TimerFunction();
    void GenerateTestOrder();

protected:

    InterfaceManager* Interfaces;
    FTimerHandle GameTimerHandle;
    std::unordered_set<int> TestOrder;
    float GameTimer = 5.0f;
    int32 NumExperiments = 1;
};
