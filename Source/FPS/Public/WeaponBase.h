// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireModeEnum.h"
#include "WeaponBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnShootSignature)

UENUM()
enum EFireMode
{
	Semi UMETA(DisplayName = "Semi Automatic"),
	Auto UMETA(DisplayName = "Automatic")

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

	/* Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	USkeletalMeshComponent* WeaponBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* ForestockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* IronSightFrontMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* IronSightBackMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* MagazineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* GripMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* MuzzleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* LaserBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* LaserBeamMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComponents)
	UStaticMeshComponent* MagazineReserveMesh;

public:

	UPROPERTY(EditAnywhere)
	bool bHasMuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	TEnumAsByte<EFireMode> FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	class UGripDataAsset* GripData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	class UDataAsset* MuzzleData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	float ClassicPoseValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	float AimRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	float ShootDelay;

	EFireMode GetFireMode() const { return FireMode; }
	float GetFireRate() const { return FireRate; }
	float GetClassicPoseValue() const { return ClassicPoseValue; }
	float GetAimRate() const { return AimRate; }
	float GetShootDelay() const { return ShootDelay; }

	/* Visuals */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Particles")
	class UParticleSystem* MuzzleFlash;

	/* Animation */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* ArmsFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* ArmsAimFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* WeaponFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* ArmsUnholsterMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	UAnimMontage* WeaponUnholsterMontage;

	/* Fire Handle */
	FTimerHandle FireRateHandle;
	FTimerHandle ShootDelayHandle;


public:

	/* Fire Actions */

	UFUNCTION()
	void PlayWeaponSFX(const UWorld* World);

	UFUNCTION()
	void PlayFireMontages(AFPSCharacter* OwnerCharacter);

	UFUNCTION()
	void SpawnMuzzleFlash();

	UFUNCTION()
	void PlayWeaponUnholsterMontage(AFPSCharacter* Character, AWeaponBase* CurrentWeapon);

	UFUNCTION()
	void SetupWeaponAttachment(AFPSCharacter* Character, AActor* CurrentWeaponActor);

	UFUNCTION()
	void SetupWeaponInput(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon);

};