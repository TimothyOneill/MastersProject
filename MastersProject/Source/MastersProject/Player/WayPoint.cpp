#include "MastersProject.h"
#include "MainPlayer.h"
#include "../MetricTracker.h"
#include "WayPoint.h"

// Sets default values
AWayPoint::AWayPoint()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UDataTable> WayPointLocations_BP(TEXT("DataTable'/Game/StarterContent/Blueprints/WayPointLocations.WayPointLocations'"));
    WayPointLocations = WayPointLocations_BP.Object;

    // Have to apply a -1 here to remove the title row.
    // TODO Only Works With Editor Builds
    NumberOfWaypoints = 5; //WayPointLocations->GetTableData().Num();
}

void AWayPoint::Destroyed()
{
    if (Marker)
    {
        Marker->Destroy();
    }
}

// Called when the game starts or when spawned
void AWayPoint::BeginPlay()
{
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

// Called every frame
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
    PassedTime = FDateTime::Now().GetSecond() - StartTime;
    FString WaypointString = FString::Printf(TEXT("Location%d"), CollisionCount);
    FString PassedTimeString = FString::Printf(TEXT("%d,"), PassedTime);
    MetricTracker::Instance()->ReportContinousMetric(WaypointString, PassedTimeString);
}

void AWayPoint::MoveNextLocation()
{
    StartTime = FDateTime::Now().GetSecond();
    LocationsRow = WayPointLocations->FindRow<FWayPointLocations>(*FString::Printf(TEXT("Location%d"), CollisionCount), TEXT("WayPointLocations"));
    SetActorLocation(LocationsRow->Location, false);
    if (Marker)
    {
        Marker->SetActorLocation(LocationsRow->Location, false);
    }
}

