#include "MastersProject.h"
#include "DiegeticInterface.h"

UDiegeticInterface::UDiegeticInterface()
{
    // Sets the Blueprint class for the handscanner.
    static ConstructorHelpers::FClassFinder<AActor> HandScanner(TEXT("Blueprint'/Game/MastersProject/Blueprints/Actors/A_HandScanner.A_HandScanner_C'"));
    if (HandScanner.Class != NULL)
    {
        HandScannerBP = HandScanner.Class;
    }

    // Sets the Blueprint class for the 3DWidget which is used to draw the interface.
    static ConstructorHelpers::FClassFinder<AActor> Widget(TEXT("Blueprint'/Game/MastersProject/Blueprints/Actors/A_DiegeticInterface.A_DiegeticInterface_C'"));
    if (Widget.Class != NULL)
    {
        WidgetBP = Widget.Class;
    }
}

// Init methods allow us to only intialize when we actually need the interface.
void UDiegeticInterface::Init()
{
    DiegeticModel = SpawnBP<AActor>(GWorld, HandScannerBP, FVector(0, 0, 10), FRotator(0, 0, 0));
    DiegeticModel->SetActorEnableCollision(false);
    Interface3D = SpawnBP<AActor>(GWorld, WidgetBP, FVector(0, 0, 10), FRotator(0, 0, 0));
    Interface3D->AttachRootComponentToActor(DiegeticModel, "Screen");
    OwningPlayer = UGameplayStatics::GetPlayerController(GWorld, 0);
    DiegeticModel->AttachRootComponentToActor(OwningPlayer->GetPawn(), "Scanner");
}

// Sets the Tick of the interface to allow it to render and update.
bool UDiegeticInterface::IsTickable() const
{
    return CanTick;
}

// Inherited method.
TStatId UDiegeticInterface::GetStatId() const
{
    return TStatId();
}

//Called as the object is destroyed tidy's up its sub components.
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
