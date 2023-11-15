// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponRifle.h"

AWeaponRifle::AWeaponRifle()
{
	WeaponBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponBody->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(WeaponBody, "SOCKET_Forestock");

	IronSightBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Back Mesh"));
	IronSightBackMesh->SetupAttachment(WeaponBody, "SOCKET_Scope");

	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Mesh"));
	MagazineMesh->SetupAttachment(WeaponBody, "SOCKET_Magazine");

	IronSightFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Front Mesh"));
	IronSightFrontMesh->SetupAttachment(ForestockMesh, "SOCKET_Ironsight_F");

	GripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip Mesh"));
	GripMesh->SetupAttachment(ForestockMesh, "SOCKET_Grip");
}
