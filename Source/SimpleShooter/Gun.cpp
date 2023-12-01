// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));


	FHitResult HitResult;
	FVector ShotDirection;

	bool bSuccess = GunTrace(HitResult, ShotDirection);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint - GetOwner()->GetActorForwardVector()*5.f, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactMuzzleSound, HitResult.ImpactPoint);
	
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			AController* OwnerController = GetOwnerController();
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

AController *AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn==nullptr){return nullptr;}
	return OwnerPawn->GetController();
}

bool AGun::GunTrace(FHitResult &OutHitResult, FVector &OutShotDirection)
{
	AController* OwnerController = GetOwnerController();

	if (OwnerController==nullptr){return false;}

	FVector StartLocation;
	FRotator StartRotation;
	OwnerController->GetPlayerViewPoint(StartLocation, StartRotation);

	FVector EndLocation = StartLocation + StartRotation.Vector()*MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool HasHit = GetWorld()->LineTraceSingleByChannel(OutHitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, Params);

	OutShotDirection = -StartRotation.Vector();

	return HasHit;


	return true;


	
}
