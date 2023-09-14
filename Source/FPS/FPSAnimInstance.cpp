// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAnimInstance.h"
#include "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFPSAnimInstance::NativeInitializeAnimation()
{
	FPSCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
}

void UFPSAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	const AFPSCharacter* Character = GetFPSCharacter();

	if (Character != nullptr)
	{
		//Set Forward + Right Velocity Normalized
		FVector Forward = Character->GetActorForwardVector();
		FVector Right = Character->GetActorRightVector();
		FVector VelocityNormalized = Character->GetVelocity().GetSafeNormal();

		//Set Normlaized Normailzed
		ForwardVelocityNormalized = FVector::DotProduct(Forward, VelocityNormalized);
		RightVelocityNormalized = FVector::DotProduct(Right, VelocityNormalized);

		//Lerp Normalized Velocity 
		ForwardVelocityLerpValue = FMath::Lerp(ForwardVelocityLerpValue, ForwardVelocityNormalized, DeltaTime * VelocityLerpSpeed);
		RightVelocityLerpValue = FMath::Lerp(RightVelocityLerpValue, RightVelocityNormalized, DeltaTime * VelocityLerpSpeed);

		//Set Character Properties
		bIsInAir = Character->GetCharacterMovement()->IsFalling();
		bIsAiming = Character->bIsAiming;
		bIsSprinting = Character->bIsSprinting;
		bIsShooting = Character->bIsShooting;
	}
}
