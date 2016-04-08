#pragma once
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class MASTERSPROJECT_API AAsteroid : public AActor
{
    GENERATED_BODY()
public:

    AAsteroid();
    void Init(FVector Target);
    void Destroyed() override;

    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    UFUNCTION()
    virtual void OnOverlap(AActor* OtherActor);

    void ShowMarker() { Marker->SetActorHiddenInGame(false); };
    void HideMarker() { Marker->SetActorHiddenInGame(true); };
    bool DetectPlayer();
    void HasPlayerDodged();

    UPROPERTY(EditAnywhere, Category = "Marker", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> MarkerBP;

private:

    FVector Target = FVector(0.0f, 0.0f, 0.0f);
    FVector DirectionVector = FVector(0.0f, 0.0f, 0.0f);
    AActor* Marker;
    const float Speed = 0.3f;
    const float DetectionRadius = 450;
    bool PlayerEnter = false;
    bool PlayerExit = false;
};
