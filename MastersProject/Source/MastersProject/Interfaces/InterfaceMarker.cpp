// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "InterfaceMarker.h"


// Sets default values
AInterfaceMarker::AInterfaceMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MarkerVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    RootComponent = MarkerVisual;

    if (MarkerStaticMesh)
    {
        MarkerVisual->SetStaticMesh(MarkerStaticMesh);
    }
}

// Called when the game starts or when spawned
void AInterfaceMarker::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInterfaceMarker::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

