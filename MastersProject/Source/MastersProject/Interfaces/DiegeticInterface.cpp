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

    static ConstructorHelpers::FObjectFinder<UBlueprint> Widget(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/Diegetic_Actor.Diegetic_Actor'"));
    if (Widget.Object)
    {
        WidgetBP = (UClass*)Widget.Object->GeneratedClass;
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
    return bTick;
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
