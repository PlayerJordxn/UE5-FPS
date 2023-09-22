// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


///* Weapon user interface */
//USTRUCT()
//struct FWeaponTextData
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere)
//	FText Name;
//
//	UPROPERTY(EditAnywhere)
//	FText CurrentAmmo;
//
//	UPROPERTY(EditAnywhere)
//	class UImage* WeaponIcon;
//};


UENUM()
enum EFireMode
{
	Auto UMETA(DisplayName = "Automatic"),
	Semi UMETA(DisplayName = "Semi Automatic"),
	Bolt UMETA(DisplayName = "Bolt Action"),
	Pump UMETA(DisplayName = "PumpAction"),
};

UCLASS()
class FPS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Input")
	class UInputMappingContext* FireContext;

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Input")
	class UInputAction* FireAction;

	// Sets default values for this actor's properties
	AWeaponBase();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* ForestockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* BarrelMesh;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	float FireRate;

	FTimerHandle FireRateHandle;

	class AFPSCharacter* OwnerCharacter;

	void AttachWeapon(class AFPSCharacter* Character, AWeaponBase* Weapon, AActor* WeaponActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UDataAsset* GripData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	TEnumAsByte<EFireMode> FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* FireAimMontage;

	void StopFire();

};