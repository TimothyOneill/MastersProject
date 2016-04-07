#include "MastersProject.h"
#include "Asteroid.h"
#include "../Player/MainPlayer.h"
#include "../MetricTracker.h"

AAsteroid::AAsteroid()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAsteroid::Destroyed()
{
    if (Marker)
    {
        Marker->Destroy();
    }
}

void AAsteroid::Init(FVector InitTarget)
{
    Target = InitTarget;
    DirectionVector = (GetActorLocation() - Target);
    DirectionVector.GetSafeNormal();
    FRotator Rotation = FRotationMatrix::MakeFromX(DirectionVector).Rotator();
    Marker = SpawnBP<AActor>(GetWorld(), MarkerBP, FVector(Target.X, Target.Y, 12), FRotator(0, 0, 0));
    Marker->SetActorEnableCollision(false);
    Marker->SetActorHiddenInGame(true);
    SetActorRotation(Rotation);
}

void AAsteroid::BeginPlay()
{
    OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlap);
    Super::BeginPlay();
}

void AAsteroid::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    FVector NewLocation = GetActorLocation() - (DirectionVector * Speed * DeltaTime);
    SetActorLocation(NewLocation, true);
}

void AAsteroid::OnOverlap(AActor* OtherActor)
{
    if (OtherActor->ActorHasTag("AsteroidCollision"))
    {
        if (OtherActor->IsA(AMainPlayer::StaticClass()))
        {
            MetricTracker::Instance()->ReportDiscreteMetric("Hit", 1);
            MetricTracker::Instance()->ClearSpecificDiscreteMetric("Streak");
            MetricTracker::Instance()->ReportContinousMetric("AllAsteroids", "1,");
        }
        MetricTracker::Instance()->ReportDiscreteMetric("Dodged", 1);
        MetricTracker::Instance()->ReportDiscreteMetric("Streak", 1);
        MetricTracker::Instance()->ReportContinousMetric("AllAsteroids", "0,");
        Destroy();
    }
}