// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM()
enum EWeaponType
{
	Rifle = 0 UMETA(DisplayName = "Rifle"),
	Pistol = 1 UMETA(DisplayName = "Pistol"),
	Sniper = 2 UMETA(DisplayName = "Sniper"),
};

UCLASS()
class FPS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	UStaticMeshComponent* ForestockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponComponents)
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponProperties)
	TEnumAsByte<EWeaponType> WeaponType;

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponProperties)
	class UInputMappingContext* FireContext;

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponProperties)
	class UInputAction* FireAction;

	void AttachWeapon(class AFPSCharacter* Character, AWeaponBase* Weapon, AActor* WeaponActor);

};