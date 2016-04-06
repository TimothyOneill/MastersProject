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

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DiegeticModel")
    UPROPERTY()
    TSubclassOf<AActor> HandScannerBP;
    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
    UPROPERTY()
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
