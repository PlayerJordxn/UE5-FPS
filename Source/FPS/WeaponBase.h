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

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AimRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FireRate;
};

UENUM()
enum EWeaponType
{
	Rifle UMETA(DisplayName = "Rifle"),
	Pistol UMETA(DisplayName = "Pistol"),
	Sniper UMETA(DisplayName = "Sniper"),
	Shotgun UMETA(DisplayName = "Shotgun"),
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

	/* Character Holding Weapon */
	class AFPSCharacter* OwnerCharacter;

	// Sets default values for this actor's properties
	AWeaponBase();

public:	

	/* Mesh */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* ForestockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* IronSightFrontMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* IronSightBackMesh;

public:

	/* Fire Handle */
	FTimerHandle FireRateHandle;

	/* Weapon Attachment*/
	void AttachWeapon(class AFPSCharacter* Character, AActor* WeaponToEquip, EWeaponType WeaponType);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	TEnumAsByte<EWeaponType> FireMode;

	void OnFire();
	void StopFire();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	UAnimMontage* UnholsterMontage;


};