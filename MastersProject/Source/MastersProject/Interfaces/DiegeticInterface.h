#pragma once
#include "DiegeticInterface.generated.h"

UCLASS(Blueprintable)
class MASTERSPROJECT_API UDiegeticInterface : public UObject, public FTickableGameObject
{
    GENERATED_BODY()
public:

    UDiegeticInterface();

    void Init();
    void EnableTick() { CanTick = true; };
    void DisableTick() { CanTick = false; };

    UPROPERTY()
    TSubclassOf<AActor> HandScannerBP;
    UPROPERTY()
    TSubclassOf<AActor> WidgetBP;

private:

    virtual void Tick(float DeltaTime) override {};
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;
    virtual void BeginDestroy() override;

    AActor* DiegeticModel;
    AActor* Interface3D;
    APlayerController* OwningPlayer;

    bool CanTick = false;
};
