// Fill out your copyright notice in the Description page of Project Settings.
#include "MastersProject.h"
#include "AsteroidSpawner.h"
#include <algorithm>

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    USphereComponent* TempSpawnerVisual = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = TempSpawnerVisual;
    SetActorEnableCollision(false);
}

void AAsteroidSpawner::Init()
{

}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
    GetWorldTimerManager().SetTimer(LocationTimerHandle, this, &AAsteroidSpawner::CalculateNextPosition, SpawnTimer, true);
    GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, SpawnTimer, true);
    DefaultLocation = GetActorLocation();
    Super::BeginPlay();
}

// Called every frame
void AAsteroidSpawner::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

void AAsteroidSpawner::RestartSpawnTimer()
{
    GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, SpawnTimer, true);
}

void AAsteroidSpawner::StopSpawnTimer()
{
    GetWorldTimerManager().ClearTimer(SpawnerTimerHandle);
}

void AAsteroidSpawner::SpawnAsteroid()
{
    //Temporary Required or ERROR:C4238 occurs
    AAsteroid* CreatedAsteroid = GetWorld()->SpawnActor<AAsteroid>(GetActorLocation(), FRotator(0,0,0));
    CreatedAsteroid->Init(target->GetActorLocation());

    //Check to make sure asteroid was spawned correctly.
    if (CreatedAsteroid)
    {
        asteroids.push_back(CreatedAsteroid);
    }
}

void AAsteroidSpawner::CalculateNextPosition()
{
    FVector NewLocation = DefaultLocation;

    NewLocation.X += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Cos(FMath::RandRange(0, 360));
    NewLocation.Y += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Sin(FMath::RandRange(0, 360));
    NewLocation.Z += std::max(SpawnRange * FMath::Sin(FMath::RandRange(0, 360)), DefaultLocation.Z);

    SetActorLocation(NewLocation);
}