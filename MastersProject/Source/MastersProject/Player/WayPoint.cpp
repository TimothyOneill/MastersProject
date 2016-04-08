#include "MastersProject.h"
#include "MainPlayer.h"
#include "../MetricTracker.h"
#include "WayPoint.h"

AWayPoint::AWayPoint()
{
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UDataTable> WayPointLocations_BP(TEXT("DataTable'/Game/StarterContent/Blueprints/WayPointLocations.WayPointLocations'"));
    WayPointLocations = WayPointLocations_BP.Object;
}

void AWayPoint::Destroyed()
{
    if (Marker)
    {
        Marker->Destroy();
    }
}

void AWayPoint::BeginPlay()
{
    NumberOfWaypoints = Cast<AMastersProjectWorldSettings>(GetWorld()->GetWorldSettings())->GetNumWaypoints();
    OnActorBeginOverlap.AddDynamic(this, &AWayPoint::OnOverlap);
    Marker = SpawnBP<AActor>(GetWorld(), MarkerBP, FVector(GetActorLocation().X, GetActorLocation().Y, 12), FRotator(0, 0, 0));
    if (Marker)
    {
        Marker->SetActorEnableCollision(false);
        Marker->SetActorHiddenInGame(true);
    }
    MoveNextLocation();
    Super::BeginPlay();
}

void AWayPoint::Tick( float DeltaTime )
{
    if (CollisionLock)
    {
        CollisionLock = false;
    }
    Super::Tick( DeltaTime );
}

void AWayPoint::OnOverlap(AActor* OtherActor)
{
    // Awfull boolean lock required due to engine bug with moving actors after an overlap.
    if (OtherActor->IsA(AMainPlayer::StaticClass()) && !CollisionLock)
    {
        CollisionLock = true;
        if (CollisionCount < NumberOfWaypoints)
        {
            CollisionCount++;
        }
        else
        {
            CollisionCount = 1;
        }
        ReportElapsedTime();
        MoveNextLocation();
    }
}

void AWayPoint::ReportElapsedTime()
{
    PassedTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - StartTime;
    FString WaypointString = FString::Printf(TEXT("Location%d"), CollisionCount);
    FString PassedTimeString = FString::Printf(TEXT("%d,"), PassedTime);
    MetricTracker::Instance()->ReportContinousMetric(WaypointString, PassedTimeString);
}

void AWayPoint::MoveNextLocation()
{
    StartTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
    LocationsRow = WayPointLocations->FindRow<FWayPointLocations>(*FString::Printf(TEXT("Location%d"), CollisionCount), TEXT("WayPointLocations"));
    SetActorLocation(LocationsRow->Location, false);
    if (Marker)
    {
        Marker->SetActorLocation(LocationsRow->Location, false);
    }
}

