// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "NonDiegeticInterface.h"

UNonDiegeticInterface::UNonDiegeticInterface()
{
    static ConstructorHelpers::FObjectFinder<UBlueprint> BluePrint(TEXT("Blueprint'/Game/StarterContent/Blueprints/Interfaces/Radar.Radar'"));
    if (BluePrint.Object)
    {
        RadarBP = (UClass*)BluePrint.Object->GeneratedClass;
    }
}

void UNonDiegeticInterface::Init()
{
    NonDiegeticModel = SpawnBP<AActor>(GWorld, RadarBP, FVector(0, 0, 0), FRotator(0, 0, 0));
    NonDiegeticModel->SetActorEnableCollision(false);
    OwningPlayer = UGameplayStatics::GetPlayerController(GWorld, 0);
}

void UNonDiegeticInterface::Tick(float DeltaTime)
{
    NonDiegeticModel->SetActorLocation(OwningPlayer->GetPawn()->GetActorLocation());
}

bool UNonDiegeticInterface::IsTickable() const
{
    return bTick;
}

TStatId UNonDiegeticInterface::GetStatId() const
{
    return TStatId();
}
