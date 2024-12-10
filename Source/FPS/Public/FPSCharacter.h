// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AWeaponBase;


UENUM(BlueprintType)
enum class PhysicalityState : uint8 {

	Crouching	UMETA(DisplayName = "Crouching"),
	Standing	UMETA(DisplayName = "Standing"),
};

UENUM(BlueprintType)
enum class MovementState : uint8 {

	Stationary	UMETA(DisplayName = "Stationary"),
	Moving		UMETA(DisplayName = "Moving"),
	Sprinting	UMETA(DisplayName = "Sprinting"),
	Airborn		UMETA(DisplayName = "Airborn"),
};


DECLARE_DELEGATE_OneParam(FOnActionRequestedSignature, PhysicalityState)

UCLASS(config=Game)
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay();

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* WeaponMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/* Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeanLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeanRightAction;


public:

	/* Rotates the camera on the pitch */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* MeshPivot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* LeanPivot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AWeaponBase> SelectedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	AWeaponBase* CurrentWeapon; 

public:

	/* Character States*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsShooting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bDisableSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsLeaningLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsLeaningRight;
	
	/* Toggles Input Binding */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toggle Input")
	bool bEnableMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toggle Input")
	bool bEnableJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toggle Input")
	bool bEnableSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toggle Input")
	bool bEnableCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toggle Input")
	bool bEnableLeaning;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Properties")
	float SprintFOV;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Properties")
	float DefaultFOV;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mouse Properties")
	float SensitivityMultiplier;

public:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for aiming input */
	void StartAim(const FInputActionValue& Value);
	void StopAim(const FInputActionValue& Value);

	/** Called for sprinting input */
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	
	/** Called for sprinting input */
	void StartCrouch(const FInputActionValue& Value);
	void StopCrouch(const FInputActionValue& Value);

	void StartFire(const FInputActionValue& Value);
	void ShootRay();
	void StopFire();

	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);

	void StartLeanLeft(const FInputActionValue& Value);
	void StartLeanRight(const FInputActionValue& Value);

	void StopLeanLeft(const FInputActionValue& Value);
	void StopLeanRight(const FInputActionValue& Value);

	void StartReload(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCrouchBegin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCrouchFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSprintBegin();	
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnSprintEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReloadStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnAimStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnAimEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeanLeftBegin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeanRightBegin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeanLeftFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeanRightFinished();



public:

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	FORCEINLINE bool IsShooting() const { return bIsShooting; }
	FORCEINLINE bool IsAiming() const { return bIsAiming; }
	FORCEINLINE bool IsSprinting() const { return bIsSprinting; }
	
private:

	UFUNCTION()
	void InitalizeWeapon();

	UFUNCTION()
	void ToggleInput();

	UFUNCTION()
	void AnimNotify_SetMagazineVisibility(bool bIsVisible);

};

