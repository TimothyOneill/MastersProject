#include "MastersProject.h"
#include "../Player/MainPlayer.h"
#include "../Utilities/MetricTracker.h"
#include "WayPoint.h"

AWayPoint::AWayPoint()
{
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UDataTable> WayPointLocations_BP(TEXT("DataTable'/Game/MastersProject/DataTables/DT_WayPointLocations.DT_WayPointLocations'"));
    WayPointLocations = WayPointLocations_BP.Object;
}

//Tidys up its Spatial marker when destoryed.
void AWayPoint::Destroyed()
{
    if (Marker)
    {
        Marker->Destroy();
    }
}

//Find out the number of waypoint locations and places the waypoint at the current location.
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
    // boolean lock required due to engine bug with moving actors after an overlap.
    // see http://tinyurl.com/hgmybn3 4.11 patch notes
    if (OtherActor->IsA(AMainPlayer::StaticClass()) && !CollisionLock)
    {
        CollisionLock = true;
        ReportElapsedTime();
        if (CollisionCount < NumberOfWaypoints)
        {
            CollisionCount++;
        }
        else
        {
            CollisionCount = 1;
        }
        MoveNextLocation();
    }
}

// Waypoint Calculate the elapsed time between waypoints being collided with and reports the metric.
void AWayPoint::ReportElapsedTime()
{
    PassedTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - StartTime;
    FString WaypointString = FString::Printf(TEXT("Location%d"), CollisionCount);
    FString PassedTimeString = FString::Printf(TEXT("%d,"), PassedTime);
    MetricTracker::Instance()->ReportContinousMetric(WaypointString, PassedTimeString);
}

//Updates where the Waypoint should mvoe to after being hit.
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

