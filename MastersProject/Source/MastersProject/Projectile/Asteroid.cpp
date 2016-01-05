// Fill out your copyright notice in the Description page of Project Settings.

#include "MastersProject.h"
#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AsteroidVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    RootComponent = AsteroidVisual;
    AsteroidVisual->SetWorldScale3D(FVector(0.8f));

    OnActorHit.AddDynamic(this, &AAsteroid::OnCollision);
    SetActorEnableCollision(true);
    //TODO Find a better way to bind a SM to C++ Class file
    static ConstructorHelpers::FObjectFinder<UStaticMesh> AsteroidVisualAsset(TEXT("/Game/StarterContent/Props/asteroid_OBJ.asteroid_OBJ"));
    if (AsteroidVisualAsset.Succeeded())
    {
       AsteroidVisual->SetStaticMesh(AsteroidVisualAsset.Object);
       //TODO Make Object Bigger in Maya
       AsteroidVisual->SetWorldScale3D(FVector(2.0f));
    }
}

void AAsteroid::Init(FVector InitTarget)
{
    Target = InitTarget;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
    DirectionVector = (GetActorLocation() - Target);
    DirectionVector.GetSafeNormal();
    FRotator Rotation = FRotationMatrix::MakeFromX(DirectionVector).Rotator();
    SetActorRotation(Rotation);
    Super::BeginPlay();
}

// Called every frame
void AAsteroid::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    FVector NewLocation = GetActorLocation() - (DirectionVector * Speed * DeltaTime);
    SetActorLocation(NewLocation);
}

void AAsteroid::OnCollision(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DeleteIng Asteroid!"));
    Destroy();
}
