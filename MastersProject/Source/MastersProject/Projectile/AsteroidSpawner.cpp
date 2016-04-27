#include "MastersProject.h"
#include "AsteroidSpawner.h"
#include <algorithm>

AAsteroidSpawner::AAsteroidSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    //Required to place in the world even tho invisible.
    SpawnerVisual = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SpawnerVisual;
    SetActorEnableCollision(false);
}

// Called when the level containing spawners loads, sets the various timers.
void AAsteroidSpawner::BeginPlay()
{
    GetWorldTimerManager().SetTimer(LocationTimerHandle, this, &AAsteroidSpawner::CalculateNextPosition, SpawnTimer, true);
    GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, SpawnTimer, true);
    DefaultLocation = GetActorLocation();
    Super::BeginPlay();
}

void AAsteroidSpawner::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

// Restarts the timer responsible for the spawning of the asteroids.
void AAsteroidSpawner::RestartSpawnTimer()
{
    GetWorldTimerManager().SetTimer(SpawnerTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, SpawnTimer, true);
}

void AAsteroidSpawner::StopSpawnTimer()
{
    GetWorldTimerManager().ClearTimer(SpawnerTimerHandle);
}

//Each Spawner type is set in editor here it creates the asteroids and sets their targets.
void AAsteroidSpawner::SpawnAsteroid()
{
    AAsteroid* CreatedAsteroid = SpawnBP<AAsteroid>(GetWorld(), AsteroidBP, GetActorLocation(), FRotator(0, 0, 0));

    switch (TargetType)
    {
    case ETargetEnum::TT_Direct : CreatedAsteroid->Init(Target->GetActorLocation()), CreatedAsteroid->SetAsteroidID("Direct");
        break;
    case ETargetEnum::TT_Around : CreatedAsteroid->Init(CalculateAroundTarget()), CreatedAsteroid->SetAsteroidID("Around");
        break;
    default: CreatedAsteroid->Init(FVector(0, 0, 0));
        break;
    }

    if (CreatedAsteroid)
    {
        Asteroids.push_back(CreatedAsteroid);
    }
}

//Calculates around a given centre point.
FVector AAsteroidSpawner::CalculateAroundTarget()
{
    FVector Origin;
    FVector BoundsExtent;
    Target->GetActorBounds(false, Origin, BoundsExtent);
    float MaxRadius = (BoundsExtent.X < BoundsExtent.Y) ? BoundsExtent.X : BoundsExtent.Y;
    float Radius = FMath::RandRange(0, MaxRadius);

    // Pick a random Point within a circle of the origin of the target.
    FMath::SRandInit(FMath::Rand());
    float Angle = 2 * PI * FMath::SRand();
    float X = Radius * FMath::Cos(Angle);
    float Y = Radius * FMath::Sin(Angle);

    return FVector(X, Y, Origin.Z);
}

//Moves the spawner to a point within a hemisphere of its starting location.
void AAsteroidSpawner::CalculateNextPosition()
{
    FVector NewLocation = DefaultLocation;

    NewLocation.X += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Cos(FMath::RandRange(0, 360));
    NewLocation.Y += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Sin(FMath::RandRange(0, 360));
    NewLocation.Z += std::max(SpawnRange * FMath::Sin(FMath::RandRange(0, 360)), DefaultLocation.Z);

    SetActorLocation(NewLocation);
}