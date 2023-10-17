// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAnimInstance.h"
#include "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponBase.h"
void UFPSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	FPSCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
}

void UFPSAnimInstance::UpdateAnimationProperties(float DeltaTime)
{

	if (GetFPSCharacter() != nullptr)
	{
		//Set Forward + Right Velocity Normalized
		FVector Forward = GetFPSCharacter()->GetActorForwardVector();
		FVector Right = GetFPSCharacter()->GetActorRightVector();
		FVector VelocityNormalized = GetFPSCharacter()->GetVelocity().GetSafeNormal();

		//Set Normlaized Normailzed
		ForwardVelocityNormalized = FVector::DotProduct(Forward, VelocityNormalized);
		RightVelocityNormalized = FVector::DotProduct(Right, VelocityNormalized);

		//Lerp Normalized Velocity 
		ForwardVelocityLerpValue = FMath::Lerp(ForwardVelocityLerpValue, ForwardVelocityNormalized, DeltaTime * VelocityLerpSpeed);
		RightVelocityLerpValue = FMath::Lerp(RightVelocityLerpValue, RightVelocityNormalized, DeltaTime * VelocityLerpSpeed);

		//Set Character Properties
		bIsInAir = GetFPSCharacter()->GetCharacterMovement()->IsFalling();
		bIsAiming = GetFPSCharacter()->bIsAiming;
		bIsSprinting = GetFPSCharacter()->bIsSprinting;
		bIsShooting = GetFPSCharacter()->bIsShooting;

		if (FPSCharacter->CurrentWeapon != nullptr)
		{
			if (FPSCharacter->CurrentWeapon->GripData != nullptr)
			{
				if (GripData == nullptr)
				{
					GripData = FPSCharacter->CurrentWeapon->GripData;
				}
			}
		}
	}
}
