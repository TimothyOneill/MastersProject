// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "DiegeticInterface.h"

UDiegeticInterface::UDiegeticInterface()
{
    static ConstructorHelpers::FObjectFinder<UBlueprint> HandScanner(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/HandScaner.HandScaner'"));
    if (HandScanner.Object)
    {
        HandScannerBP = (UClass*)HandScanner.Object->GeneratedClass;
    }

    static ConstructorHelpers::FObjectFinder<UBlueprint> InterfaceVisual(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/Radar_Marker.Radar_Marker'"));
    if (InterfaceVisual.Object)
    {
        InterfaceVisualBP = (UClass*)InterfaceVisual.Object->GeneratedClass;
    }
}

void UDiegeticInterface::Init()
{
    DiegeticModel = SpawnBP<AActor>(GWorld, HandScannerBP, FVector(0, 0, 10), FRotator(0, 0, 0));
    DiegeticModel->SetActorEnableCollision(false);
    OwningPlayer = UGameplayStatics::GetPlayerController(GWorld, 0);
    DiegeticModel->AttachRootComponentToActor(OwningPlayer->GetPawn(), "Scanner");
}

void UDiegeticInterface::Tick(float DeltaTime)
{
    if (InterfaceMarks.size() < 10)
    {
        AInterfaceMarker* CreatedMark = SpawnBP<AInterfaceMarker>(GWorld, InterfaceVisualBP, FVector(0, 0, 40), FRotator(0, 0, 0));
        //Get Current Asteroid at the top and spawn marker suitably relative to the player.
        if (CreatedMark)
        {
            CreatedMark->Init();
            CreatedMark->AttachRootComponentToActor(DiegeticModel);
            CreatedMark->SetActorLocation(CreatedMark->GetActorLocation()+FVector(46.2f, -32, 40));
            InterfaceMarks.push_back(CreatedMark);
        }
    }
}

bool UDiegeticInterface::IsTickable() const
{
    return bTick;
}

TStatId UDiegeticInterface::GetStatId() const
{
    return TStatId();
}
