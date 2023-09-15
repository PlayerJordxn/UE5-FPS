// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponPistol.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AWeaponPistol : public AWeaponBase
{
	GENERATED_BODY()

public:

	AWeaponPistol();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;	

};
