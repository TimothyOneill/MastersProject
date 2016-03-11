// Fill out your copyright notice in the Description page of Project Settings.
#include "MastersProject.h"
#include "AsteroidSpawner.h"
#include <algorithm>

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    //Required to place in the world.
    SpawnerVisual = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SpawnerVisual;
    SetActorEnableCollision(false);
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
    AAsteroid* CreatedAsteroid = SpawnBP<AAsteroid>(GetWorld(), AsteroidBP, GetActorLocation(), FRotator(0, 0, 0));

    switch (TargetType)
    {
    case ETargetEnum::TT_Direct : CreatedAsteroid->Init(target->GetActorLocation());
        break;
    case ETargetEnum::TT_Around : CreatedAsteroid->Init(CalculateAroundTarget());
        break;
    default: CreatedAsteroid->Init(FVector(0, 0, 0));
        break;
    }

    //Check to make sure asteroid was spawned correctly.
    if (CreatedAsteroid)
    {
        asteroids.push_back(CreatedAsteroid);
    }
}

FVector AAsteroidSpawner::CalculateAroundTarget()
{
    FVector Origin;
    FVector BoundsExtent;
    target->GetActorBounds(false, Origin, BoundsExtent);
    float XRange = BoundsExtent.X /2;
    float YRange = BoundsExtent.Y /2;

    return FVector(FMath::RandRange(Origin.X - XRange, Origin.X + XRange), FMath::RandRange(Origin.Y - YRange, Origin.Y + YRange), Origin.Z);
}

void AAsteroidSpawner::CalculateNextPosition()
{
    FVector NewLocation = DefaultLocation;

    NewLocation.X += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Cos(FMath::RandRange(0, 360));
    NewLocation.Y += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Sin(FMath::RandRange(0, 360));
    NewLocation.Z += std::max(SpawnRange * FMath::Sin(FMath::RandRange(0, 360)), DefaultLocation.Z);

    SetActorLocation(NewLocation);
}