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

	/* Character Holding Weapon */
	class AFPSCharacter* OwnerCharacter;

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

public:

	UPROPERTY(EditAnywhere)
	bool bHasMuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Statistics")
	TEnumAsByte<EFireMode> FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	class UGripDataAsset* GripData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	class UDataAsset* MuzzleData;

	FOnShootSignature OnShoot;

	EFireMode GetFireMode() const { return FireMode; }
	float GetFireRate() const { return .02f; }
	float GetClassicPoseValue() const { return 0.f; }
	float GetAimRate() const { return .2f; }


	UFUNCTION()
	void AttachWeapon(class AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon);

	void PlayWeaponUnholsterMontage(AFPSCharacter* Character, AWeaponBase* CurrentWeapon);

	void SetupWeaponAttachment(AActor* CurrentWeaponActor, AFPSCharacter* Character);

	UFUNCTION()
	void SetupWeaponInput(AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon);
	
	UFUNCTION()
	void SetupWeaponVFX(AWeaponBase* CurrentWeapon);

	UFUNCTION()
	void SetupWeaponAnimations(UWorld* const& World, AFPSCharacter* Character, AWeaponBase* CurrentWeapon);

	UFUNCTION()
	void OnFirePressed();

	UFUNCTION()
	void OnFireRelased();

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
	FTimerHandle WeaponSwayHandle;


private:

	/* Fire Actions */

	UFUNCTION()
	void PlayWeaponSFX();

	UFUNCTION()
	void PlayFireMontages();

	UFUNCTION()
	void SpawnMuzzleFlash();
};