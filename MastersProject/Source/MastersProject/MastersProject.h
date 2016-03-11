// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Engine.h"

//TODO AddSource
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