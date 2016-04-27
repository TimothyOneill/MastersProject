#include "MastersProject.h"
#include "MastersProjectGameMode.h"

AMastersProjectGameMode::AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Interfaces = new InterfaceManager();
}

//Called at the point of the level loading.
void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();
    NumExperiments = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetNumExperiments();
    GenerateTestOrder();
    ChangeTestScenario();
}

//Called after level loading when the match begins.
void AMastersProjectGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    GameTimer = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetGameTimer();
    RestartGameTimer();
}

//At the end of the experiment returns the user to the main menu.
void AMastersProjectGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();
    StopGameTimer();
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

// Resets the timer responsible for changing the interface after X seconds.
void AMastersProjectGameMode::RestartGameTimer()
{
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectGameMode::TimerFunction, GameTimer, true);
}

void AMastersProjectGameMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}

//Calls Interfacemanager to change the interface to the correct Enum also sets the section header in the Metric Tracker.
void AMastersProjectGameMode::ChangeTestScenario()
{
    switch (*TestOrder.begin())
    {
    
    case 0 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_DiegeticInterface), MetricTracker::Instance()->SetSectionName("Digetic Interface");
        break;
    case 1 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_NonDiegeticInterface), MetricTracker::Instance()->SetSectionName("Non Digetic Interface");
        break;
    case 2 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_MetaInterface), MetricTracker::Instance()->SetSectionName("Meta Interface");
        break;
    case 3 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_SpatialInterface), MetricTracker::Instance()->SetSectionName("Spatial Interface");
        break;
    case 4 : TestOrder.erase(TestOrder.begin()), Interfaces->ChangeInterface(EInterfaceEnum::IE_NoInterface), MetricTracker::Instance()->SetSectionName("No Interface");
        break;
    default : StopGameTimer(), SetMatchState(MatchState::WaitingPostMatch);
        break;
    }
}

//Clears Writes stored metrics and clears them then changes the interface.
void AMastersProjectGameMode::TimerFunction()
{
    MetricTracker::Instance()->WriteMetricsToFile();
    MetricTracker::Instance()->ClearAllMetrics();
    ChangeTestScenario();
}

//By using an unordered we can get one instance of every number between 0 and Num experiments in a random order.
void AMastersProjectGameMode::GenerateTestOrder()
{
    while (TestOrder.size() != NumExperiments)
    {
        TestOrder.insert(FMath::RandRange(0, NumExperiments-1));
    }
}
