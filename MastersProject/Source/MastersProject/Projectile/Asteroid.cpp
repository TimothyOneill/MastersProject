// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "Asteroid.h"
#include "../MetricTracker.h"

// Sets default values
AAsteroid::AAsteroid()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AsteroidVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    AsteroidVisual->SetCastShadow(false);
    RootComponent = AsteroidVisual;

    if (AsteroidStaticMesh)
    {
        AsteroidVisual->SetStaticMesh(AsteroidStaticMesh);
    }
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
    OnActorHit.AddDynamic(this, &AAsteroid::OnCollision);
    OnActorBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlap);
    Super::BeginPlay();
}

// Called every frame
void AAsteroid::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    FVector NewLocation = GetActorLocation() - (DirectionVector * Speed * DeltaTime);
    SetActorLocation(NewLocation);
}

void AAsteroid::OnCollision(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Deleting Asteroid!"));
    MetricTracker::Instance()->ReportDiscreteMetric("Hit", 1);
    MetricTracker::Instance()->ClearSpecificDiscreteMetric("Streak");
    MetricTracker::Instance()->ReportContinousMetric("AllAsteroids", "1,");
    Destroy();
}

//Required due a bug I found in UE4 UE-26257
void AAsteroid::OnOverlap(AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this))
    {
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Deleting Asteroid that hit Platform!"));
        MetricTracker::Instance()->ReportDiscreteMetric("Dodged", 1);
        MetricTracker::Instance()->ReportDiscreteMetric("Streak", 1);
        MetricTracker::Instance()->ReportContinousMetric("AllAsteroids", "0,");
        Destroy();
    }
}
