// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


/* Weapon user interface */
USTRUCT()
struct FWeaponTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText CurrentAmmo;

	UPROPERTY(EditAnywhere)
	class UImage* WeaponIcon;
};

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
enum EFireMode
{
	Semi UMETA(DisplayName = "Semi Automatic"),
	Auto UMETA(DisplayName = "Automatic"),
	Pump UMETA(DisplayName = "Pump Action"),
	Bolt UMETA(DisplayName = "Bolt Action"),
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

	FORCEINLINE EFireMode GetWeaponType() const { return FireMode; }
	FORCEINLINE float GetFireRate() const { return FireRate; }

	void AttachWeapon(class AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon);
	void BindWeaponInput(AWeaponBase* CurrentWeapon, AActor* CurrentWeaponActor, class UEnhancedInputComponent* EnhancedInputComponent);
	
	void OnFireSemiAutomatic();
	void OnFireAutomatic();

	void EndFire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	TEnumAsByte<EFireMode> FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Properties")
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Particles")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* MuzzleFlashSocket;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	UAnimMontage* ArmsFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	UAnimMontage* WeaponFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	UAnimMontage* ArmsUnholsterMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Animations")
	UAnimMontage* WeaponUnholsterMontage;

	TSubclassOf<AActor*> BulletCase;

	TArray<AActor*> BulletPool;

	/* Fire Handle */
	FTimerHandle FireRateHandle;

};