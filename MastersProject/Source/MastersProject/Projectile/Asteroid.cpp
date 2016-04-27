#include "MastersProject.h"
#include "Asteroid.h"
#include "../Player/MainPlayer.h"
#include "../Utilities/MetricTracker.h"

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

//Init allows the asteroids to be Constructed at another time by their creator.
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
    MetricTracker::Instance()->ReportDiscreteMetric("TotalAsteroids", 1);
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
    HasPlayerDodged();
}

//On overlapping checks what was collided with and updates the corresponding metrics and deletes it self.
void AAsteroid::OnOverlap(AActor* OtherActor)
{
    if (OtherActor->ActorHasTag("AsteroidCollision"))
    {
        if (OtherActor->IsA(AMainPlayer::StaticClass()))
        {
            MetricTracker::Instance()->ReportDiscreteMetric("Hit", 1);
        }
        if (PlayerExit)
        {
            FString MetricTitle = AsteroidID + " - Dodged";
            MetricTracker::Instance()->ReportDiscreteMetric(MetricTitle, 1);
        }
        Destroy();
    }
}

bool AAsteroid::DetectPlayer()
{
    APawn* MainPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    FVector PlayerPosition = MainPlayer->GetActorLocation();

    // Check if the player is in our detection radius ^2 is faster than Square Root
    float PlayerPointX = FMath::Pow((Target.X - PlayerPosition.X), 2);
    float PlayerPointY = FMath::Pow((Target.Y - PlayerPosition.Y), 2);

    return (PlayerPointX + PlayerPointY) < FMath::Pow(DetectionRadius,2) ? true : false;
}

// Alters the boolean states as to whether the player has dodged leads to neater code.
void AAsteroid::HasPlayerDodged()
{
    if (DetectPlayer())
    {
        PlayerEnter = true;
        PlayerExit = false;
    }
    else if (PlayerEnter)
    {
        PlayerExit = true;
        PlayerEnter = false;
    }
}

FString AAsteroid::GetAsteroidID()
{
    return AsteroidID;
}

void AAsteroid::SetAsteroidID(FString NewAsteroidID)
{
    AsteroidID = NewAsteroidID;
}