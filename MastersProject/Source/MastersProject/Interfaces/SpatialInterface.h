#pragma once
#include "Projectile/Asteroid.h"
#include "SpatialInterface.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSPROJECT_API USpatialInterface : public UObject, public FTickableGameObject
{
    GENERATED_BODY()
public:
    USpatialInterface();
    void EnableTick() { bTick = true; };
    void DisableTick() { bTick = false; };
    void HideMarkers();

private:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;

    bool bTick = false;
};
