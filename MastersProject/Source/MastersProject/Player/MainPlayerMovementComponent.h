#pragma once
#include "GameFramework/PawnMovementComponent.h"
#include "MainPlayerMovementComponent.generated.h"

UCLASS()
class MASTERSPROJECT_API UMainPlayerMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()
public:

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

    const float Gravity = 9.8f;
};
