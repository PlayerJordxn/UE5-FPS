// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UFPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:


	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

public:
	
	class AFPSCharacter* FPSCharacter;

	float ForwardVelocityNormalized;

	float RightVelocityNormalized;

	UFUNCTION(BlueprintCallable)
	AFPSCharacter* GetFPSCharacter() const { return FPSCharacter; }


protected:

	//Forward + Back Movement Lerped - Normalized
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ForwardVelocityLerpValue;
	
	//Right + Left Movement Lerped - Normalized
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float RightVelocityLerpValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float VelocityLerpSpeed = 5.0f;

	//Player Conditions
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsAiming;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsShooting;

};
