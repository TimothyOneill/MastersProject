#pragma once
#include "GameFramework/GameMode.h"
#include "Interfaces/InterfaceManager.h"
#include "MastersProjectDemoMode.generated.h"

/**
* MastersProjectDemoMode Defines the rule set for the demo version for experiment
* While similar to the main game mode allows for future work of interfactive tutorial
* Or a more complex demo, due to it being its own seperate clas.
**/

UCLASS()
class MASTERSPROJECT_API AMastersProjectDemoMode : public AGameMode
{
    GENERATED_BODY()
public:

    AMastersProjectDemoMode(const FObjectInitializer& ObjectInitializer);

    virtual void StartPlay() override;
    virtual void HandleMatchHasStarted();
    virtual void HandleMatchHasEnded();

    void RestartGameTimer();
    void StopGameTimer();
    void ChangeTestScenario();

protected:

    InterfaceManager* Interfaces;
    FTimerHandle GameTimerHandle;
    float GameTimer = 5.0f;
    int CurrentInterface = 0;
};
