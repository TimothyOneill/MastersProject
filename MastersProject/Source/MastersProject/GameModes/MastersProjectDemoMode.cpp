#include "MastersProject.h"
#include "../Utilities/MastersProjectWorldSettings.h"
#include "../Utilities/MetricTracker.h"
#include "MastersProjectDemoMode.h"

AMastersProjectDemoMode::AMastersProjectDemoMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Interfaces = new InterfaceManager();
}

//Called when the level loads.
void AMastersProjectDemoMode::StartPlay()
{
    Super::StartPlay();
    ChangeTestScenario();
}

//Called After Startplay when the match starts.
void AMastersProjectDemoMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    GameTimer = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetDemoTimer();
    RestartGameTimer();
}

void AMastersProjectDemoMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();
    MetricTracker::Instance()->ClearAllMetrics();
    StopGameTimer();
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

//Resets the game timer responsible for changing the interfaces after X seconds.
void AMastersProjectDemoMode::RestartGameTimer()
{
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectDemoMode::ChangeTestScenario, GameTimer, true);
}

void AMastersProjectDemoMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}

//Calls the interfaceManager with the Enum of the new interface.
void AMastersProjectDemoMode::ChangeTestScenario()
{
    switch (CurrentInterface)
    {
    case 0: Interfaces->ChangeInterface(EInterfaceEnum::IE_DiegeticInterface);
        break;
    case 1: Interfaces->ChangeInterface(EInterfaceEnum::IE_NonDiegeticInterface);
        break;
    case 2: Interfaces->ChangeInterface(EInterfaceEnum::IE_MetaInterface);
        break;
    case 3: Interfaces->ChangeInterface(EInterfaceEnum::IE_SpatialInterface);
        break;
    case 4: Interfaces->ChangeInterface(EInterfaceEnum::IE_NoInterface);
        break;
    default: StopGameTimer(), SetMatchState(MatchState::WaitingPostMatch);
        break;
    }
    CurrentInterface++;
}