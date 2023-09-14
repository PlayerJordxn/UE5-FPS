// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPistol.h"

AWeaponPistol::AWeaponPistol()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(Weapon, "SOCKET_Slide");

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(Weapon, "SOCKET_Default");
}

void AWeaponPistol::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Shoot()
{

}
