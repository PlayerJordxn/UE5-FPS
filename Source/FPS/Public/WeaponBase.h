// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireModeEnum.h"
#include "WeaponBase.generated.h"

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
	USkeletalMeshComponent* Weapon;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* MuzzleFlashSocket;

	void OnFirePressed();
	void OnFireRelased();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Statistics")
	TEnumAsByte<EFireMode> FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Statistics")
	class UGripDataAsset* GripData;

	EFireMode GetFireMode() const { return FireMode; }
	float GetFireRate() const { return .02f; }
	float GetClassicPoseValue() const { return 0.f; }
	float GetAimRate() const { return .2f; }

	UFUNCTION()
	void AttachWeapon(class AFPSCharacter* Character, AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon);

	UFUNCTION()
	void BindWeaponInput(AActor* CurrentWeaponActor, AWeaponBase* CurrentWeapon, class UEnhancedInputComponent* EnhancedInputComponent);

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


	

};