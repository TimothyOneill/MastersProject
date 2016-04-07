#pragma once
#include "GameFramework/GameMode.h"
#include "Interfaces/InterfaceManager.h"
#include "MastersProjectDemoMode.generated.h"

UCLASS()
class MASTERSPROJECT_API AMastersProjectDemoMode : public AGameMode
{
    GENERATED_BODY()
public:

    AMastersProjectDemoMode(const FObjectInitializer& ObjectInitializer);

    //Transitions to Waiting to Start.
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
