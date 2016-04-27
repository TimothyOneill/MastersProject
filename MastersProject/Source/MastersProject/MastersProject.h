#pragma once
#include "Engine.h"

// Global Template function to allow easy and neat spawning of Blueprint Actors into the world.
// Taken from forum post http://tinyurl.com/zt8g769 credit to user Rama.
template <typename SpawnWorldBP>
FORCEINLINE SpawnWorldBP* SpawnBP(
    UWorld* TheWorld,
    UClass* TheBP,
    const FVector& Loc,
    const FRotator& Rot,
    AActor* Owner = NULL,
    APawn* Instigator = NULL
    ) {
    if (!TheWorld) return NULL;
    if (!TheBP) return NULL;

    FActorSpawnParameters SpawnInfo;
    SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
    SpawnInfo.Owner = Owner;
    SpawnInfo.Instigator = Instigator;
    SpawnInfo.bDeferConstruction = false;

    return TheWorld->SpawnActor<SpawnWorldBP>(TheBP, Loc, Rot, SpawnInfo);
}