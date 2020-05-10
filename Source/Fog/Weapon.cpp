// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "WeaponStructures.h"
#include "Components/StaticMeshComponent.h"
#include "FightCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetIsReplicated(true);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
		Mesh->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnOverlapEnd);
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SetWeaponData(FWeaponInfo* NewWeaponData)
{
	if (!NewWeaponData || !NewWeaponData->Mesh) return;

	WeaponData = NewWeaponData;
	
	Mesh->SetStaticMesh(WeaponData->Mesh);
}

void AWeapon::EnableCollisionCheck()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWeapon::DisableCollisionCheck()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFightCharacter* MyCharacter = Cast<AFightCharacter>(GetParentActor());
	if (!MyCharacter) return;

	AFightCharacter* AttackedCharacter = Cast<AFightCharacter>(OtherActor);
	if (!AttackedCharacter) return;

	if (MyCharacter->IsEnemy(AttackedCharacter))
	{
		UGameplayStatics::ApplyDamage(AttackedCharacter, WeaponData->Damage, nullptr, this, UDamageType::StaticClass());
	}

}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

}