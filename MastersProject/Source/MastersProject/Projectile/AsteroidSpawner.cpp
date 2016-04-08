#include "MastersProject.h"
#include "AsteroidSpawner.h"
#include <algorithm>

AAsteroidSpawner::AAsteroidSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    //Required to place in the world.
    SpawnerVisual = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    RootComponent = SpawnerVisual;
    SetActorEnableCollision(false);
}

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
    float MaxRadius = (BoundsExtent.X < BoundsExtent.Y) ? BoundsExtent.X : BoundsExtent.Y;
    float Radius = FMath::RandRange(0, MaxRadius);

    // Pick a random Point within a circle of the origin of the target.
    FMath::SRandInit(FMath::Rand());
    float Angle = 2 * PI * FMath::SRand();
    float X = Radius * FMath::Cos(Angle);
    float Y = Radius * FMath::Sin(Angle);

    return FVector(X, Y, Origin.Z);
}

void AAsteroidSpawner::CalculateNextPosition()
{
    FVector NewLocation = DefaultLocation;

    NewLocation.X += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Cos(FMath::RandRange(0, 360));
    NewLocation.Y += SpawnRange * FMath::Cos(FMath::RandRange(0, 360)) * FMath::Sin(FMath::RandRange(0, 360));
    NewLocation.Z += std::max(SpawnRange * FMath::Sin(FMath::RandRange(0, 360)), DefaultLocation.Z);

    SetActorLocation(NewLocation);
}