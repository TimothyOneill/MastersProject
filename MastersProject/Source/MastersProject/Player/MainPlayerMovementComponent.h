#pragma once
#include "GameFramework/PawnMovementComponent.h"
#include "MainPlayerMovementComponent.generated.h"

/**
* MainPlayerComponent allows us to describe a players movement in serperate class
* Many MovementComponents can be created and swapped in at runtime.
**/

UCLASS()
class MASTERSPROJECT_API UMainPlayerMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()
public:

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

    const float Gravity = 9.8f;
    int32 LastTime;
};
