// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "Asteroid.h"
#include "../Player/MainPlayer.h"
#include "../MetricTracker.h"

// Sets default values
AAsteroid::AAsteroid()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
    OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlap);
    Super::BeginPlay();
}

// Called every frame
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