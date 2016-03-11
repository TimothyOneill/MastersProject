// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectGameMode.h"

AMastersProjectGameMode::AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    SpatialInterface = NewObject<USpatialInterface>(USpatialInterface::StaticClass());
    DiegeticInterface = NewObject<UDiegeticInterface>(UDiegeticInterface::StaticClass());
    NonDiegeticInterface = NewObject<UNonDiegeticInterface>(/*UNonDiegeticInterface::StaticClass()*/);
    //UMetaInterface* MetaInterface = NewObject<UMetaInterface>(/*UMetaInterface::StaticClass()*/);
    Interfaces.push_back(SpatialInterface);
    Interfaces.push_back(DiegeticInterface);
    Interfaces.push_back(NonDiegeticInterface);
}

void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();
    NonDiegeticInterface->Init();
    NonDiegeticInterface->EnableTick();
    NumExperiments = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetNumExperiments();
    GenerateTestOrder();
    ChangeTestScenario();
}

void AMastersProjectGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    GameTimer = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetGameTimer();
    RestartGameTimer();
}

void AMastersProjectGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();
    StopGameTimer();
    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void AMastersProjectGameMode::RestartGameTimer()
{
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMastersProjectGameMode::ChangeTestScenario, GameTimer, true);
}

void AMastersProjectGameMode::StopGameTimer()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle);
}

void AMastersProjectGameMode::ChangeTestScenario()
{
    switch (*TestOrder.begin())
    {
        case 0 : TestOrder.erase(TestOrder.begin()), /*_InterfaceManager->SetInterface(EInterfaceEnum::I_DiegeticInterface), _InterfaceManager->ChangeInterface(), */ MetricTracker::Instance()->SetSectionName("Digetic Interface"), MetricTracker::Instance()->WriteMetricsToFile();
        break;
        case 1 : TestOrder.erase(TestOrder.begin()), /*_InterfaceManager->SetInterface(EInterfaceEnum::I_NonDiegeticInterface), _InterfaceManager->ChangeInterface()*/ MetricTracker::Instance()->SetSectionName("Non Diegetic Interface"), MetricTracker::Instance()->WriteMetricsToFile();
        break;
        case 2 : TestOrder.erase(TestOrder.begin()), /*_InterfaceManager->SetInterface(EInterfaceEnum::I_SpatialInterface), _InterfaceManager->ChangeInterface(), */ MetricTracker::Instance()->SetSectionName("Spatial Interface"), MetricTracker::Instance()->WriteMetricsToFile();
        break;
        case 3 : TestOrder.erase(TestOrder.begin()), /*_InterfaceManager->SetInterface(EInterfaceEnum::I_MetaInterface), _InterfaceManager->ChangeInterface(), */ MetricTracker::Instance()->SetSectionName("Meta Interface"), MetricTracker::Instance()->WriteMetricsToFile();
        break;
        case 4 : TestOrder.erase(TestOrder.begin()), /*_InterfaceManager->SetInterface(EInterfaceEnum::I_NoInterface), _InterfaceManager->ChangeInterface() , */ MetricTracker::Instance()->SetSectionName("No Interface"), MetricTracker::Instance()->WriteMetricsToFile();
        break;
        default : StopGameTimer(), SetMatchState(MatchState::WaitingPostMatch), GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("End of Test Session!"));
    }
}

void AMastersProjectGameMode::GenerateTestOrder()
{
    while (TestOrder.size() != NumExperiments)
    {
        TestOrder.insert(FMath::RandRange(0, NumExperiments-1));
    }
}
