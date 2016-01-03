// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "MainPlayerMovementComponent.h"

void UMainPlayerMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //Make sure everthing is still valid and we are allowed to move
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    //ConsumeInputVector gets and then clears the vector we set in MainPlayer::Tick
    FVector movementVector(0, 0, -1);
    movementVector += ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 600.0f;
    movementVector.Z *= Gravity;

    if (!movementVector.IsNearlyZero())
    {
        FHitResult hitDetection;
        SafeMoveUpdatedComponent(movementVector, UpdatedComponent->GetComponentRotation(), true, hitDetection);

        //Apply Basic Sliding if we bump something.
        if (hitDetection.IsValidBlockingHit())
        {
            
            SlideAlongSurface(movementVector, 1.0f - hitDetection.Time, hitDetection.Normal, hitDetection);
        }
    }
}


