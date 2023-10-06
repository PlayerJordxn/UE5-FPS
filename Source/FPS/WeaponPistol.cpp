// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPistol.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

AWeaponPistol::AWeaponPistol()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(Weapon, "SOCKET_Slide");

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(Weapon, "SOCKET_Default");

	IronSightBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Back Mesh"));
	IronSightBackMesh->SetupAttachment(Weapon, "SOCKET_Ironsights");

	IronSightFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Front Mesh"));
	IronSightFrontMesh->SetupAttachment(ForestockMesh, "SOCKET_Ironsight_F");

	MuzzleFlashSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Flash Socket"));
	MuzzleFlashSocket->SetupAttachment(BarrelMesh, "SOCKET_Muzzle");
	
}

void AWeaponPistol::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	AttachWeapon(OwnerCharacter, this, this);
}

void AWeaponPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponPistol::OnFire()
{	
	if (OwnerCharacter == nullptr) return;
	if (OwnerCharacter->IsShooting()) return;

	OwnerCharacter->bIsShooting = true;
	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponPistol::EndFire, GetFireRate(), false);

	if (ArmsFireMontage != nullptr)
	{
		UAnimInstance* OwnerAnim = OwnerCharacter->GetMesh()->GetAnimInstance();
		OwnerAnim->Montage_Play(ArmsFireMontage, 1.0f);
	}

	if (WeaponFireMontage != nullptr)
	{
		Weapon->GetAnimInstance()->Montage_Play(WeaponFireMontage, 1.0f);
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}

	if (MuzzleFlash != nullptr)
	{
		FName EmitterName = "Muzzle Flash";
		FVector Location = BarrelMesh->GetRelativeLocation();
		FRotator Rotation = MuzzleFlashSocket->GetRelativeRotation();
		FVector Scale = FVector(0.2f, 0.2f, 0.2f);
		UGameplayStatics::SpawnEmitterAttached(
			MuzzleFlash, 
			MuzzleFlashSocket, 
			EmitterName,
			Location, Rotation,
			Scale);
	}
	
}

void AWeaponPistol::EndFire()
{
	OwnerCharacter->bIsShooting = false;
}


