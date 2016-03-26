// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MastersProjectGameMode.h"

AMastersProjectGameMode::AMastersProjectGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    DiegeticInterface = NewObject<UDiegeticInterface>(UDiegeticInterface::StaticClass());
    static ConstructorHelpers::FClassFinder<AHUD> HUDtest(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/Meta_Interface.Meta_Interface_C'"));
    if (HUDtest.Class != NULL) 
    {
        HUDClass = HUDtest.Class;
    }
}

void AMastersProjectGameMode::StartPlay()
{
    Super::StartPlay();
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
}

void AMastersProjectGameMode::GenerateTestOrder()
{
    while (TestOrder.size() != NumExperiments)
    {
        TestOrder.insert(FMath::RandRange(0, NumExperiments-1));
    }
}
