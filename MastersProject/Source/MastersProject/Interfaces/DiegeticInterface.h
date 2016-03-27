#pragma once
#include "DiegeticInterface.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MASTERSPROJECT_API UDiegeticInterface : public UObject, public FTickableGameObject
{
    GENERATED_BODY()
public:
    UDiegeticInterface();
    void Init();
    void EnableTick() { bTick = true; };
    void DisableTick() { bTick = false; };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DiegeticModel")
    TSubclassOf<AActor> HandScannerBP;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "3D-Widget")
    TSubclassOf<AActor> WidgetBP;
private:
    virtual void Tick(float DeltaTime) override {};
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;
    virtual void BeginDestroy() override;

    bool bTick = false;

    AActor* DiegeticModel;
    AActor* Interface3D;
    APlayerController* OwningPlayer;
};
