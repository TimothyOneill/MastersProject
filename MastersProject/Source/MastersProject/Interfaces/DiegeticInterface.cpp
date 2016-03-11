// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "DiegeticInterface.h"

UDiegeticInterface::UDiegeticInterface()
{
    static ConstructorHelpers::FObjectFinder<UBlueprint> BluePrint(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/HandScaner.HandScaner'"));
    if (BluePrint.Object)
    {
        HandScannerBP = (UClass*)BluePrint.Object->GeneratedClass;
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
    if (!PendingMarks.empty())
    {
        //Get Current Asteroid at the top and spawn marker suitably relative to the player.
        AInterfaceMarker* CreatedMark = SpawnBP<AInterfaceMarker>(GetWorld(), InterfaceVisualBP, FVector(0, 0, 0), FRotator(0, 0, 0));
        if (CreatedMark)
        {
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
