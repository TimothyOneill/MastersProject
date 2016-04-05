#pragma once
#include "WayPointLocations.generated.h"

USTRUCT (BlueprintType)
struct FWayPointLocations : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FWayPointLocations() : Location(FVector(0,0,0)) {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Warpoints)
    FVector Location;
};