#include "MastersProject.h"
#include "DiegeticInterface.h"

UDiegeticInterface::UDiegeticInterface()
{
    static ConstructorHelpers::FClassFinder<AActor> HandScanner(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/HandScaner.HandScaner_C'"));
    if (HandScanner.Class != NULL)
    {
        HandScannerBP = HandScanner.Class;
    }

    static ConstructorHelpers::FClassFinder<AActor> Widget(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/Diegetic_Actor.Diegetic_Actor_C'"));
    if (Widget.Class != NULL)
    {
        WidgetBP = Widget.Class;
    }
}

void UDiegeticInterface::Init()
{
    DiegeticModel = SpawnBP<AActor>(GWorld, HandScannerBP, FVector(0, 0, 10), FRotator(0, 0, 0));
    DiegeticModel->SetActorEnableCollision(false);
    Interface3D = SpawnBP<AActor>(GWorld, WidgetBP, FVector(0, 0, 10), FRotator(0, 0, 0));
    Interface3D->AttachRootComponentToActor(DiegeticModel, "Screen");
    OwningPlayer = UGameplayStatics::GetPlayerController(GWorld, 0);
    DiegeticModel->AttachRootComponentToActor(OwningPlayer->GetPawn(), "Scanner");
}

bool UDiegeticInterface::IsTickable() const
{
    return CanTick;
}

TStatId UDiegeticInterface::GetStatId() const
{
    return TStatId();
}

void UDiegeticInterface::BeginDestroy()
{
    if (DiegeticModel)
    {
        DiegeticModel->Destroy();
    }
    if (Interface3D)
    {
        Interface3D->Destroy();
    }
    Super::BeginDestroy();
}
