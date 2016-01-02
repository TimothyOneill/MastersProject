// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "MainPlayerCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class MASTERSPROJECT_API UMainPlayerCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
