// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponRifle.h"

AWeaponRifle::AWeaponRifle()
{
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);

	ForestockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Forestock Mesh"));
	ForestockMesh->SetupAttachment(Weapon, "SOCKET_Forestock");

	IronSightBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Back Mesh"));
	IronSightBackMesh->SetupAttachment(Weapon, "SOCKET_Scope");

	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Magazine Mesh"));
	MagazineMesh->SetupAttachment(Weapon, "SOCKET_Magazine");

	IronSightFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Iront Sight Front Mesh"));
	IronSightFrontMesh->SetupAttachment(ForestockMesh, "SOCKET_Ironsight_F");

	GripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip Mesh"));
	GripMesh->SetupAttachment(ForestockMesh, "SOCKET_Grip");
}
