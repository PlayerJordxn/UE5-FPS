// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM()
enum FireMode
{
	Auto = 0 UMETA(DisplayName = "Auto"),
	Semi = 1 UMETA(DisplayName = "Semi"),
	Bolt = 2 UMETA(DisplayName = "Bolt"),
};

UCLASS()
class FPS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	UStaticMeshComponent* ForestockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponProperties)
	TEnumAsByte<FireMode> WeaponFireMode;

	/* Shoot Type */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponProperties)
	class UInputTrigger* InputTrigger;

	void AttachWeapon(class AFPSCharacter* Character, AActor* WeaponBP);
};