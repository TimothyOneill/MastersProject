// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "../Projectile/Asteroid.h"
#include "InterfaceMarker.generated.h"

UCLASS()
class MASTERSPROJECT_API AInterfaceMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceMarker();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UStaticMesh* MarkerStaticMesh;
    UPROPERTY(VisibleAnywhere, Category = "Marker", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MarkerVisual;

private:
    AAsteroid* Marked;
    AActor* OwningPlayer;
};
