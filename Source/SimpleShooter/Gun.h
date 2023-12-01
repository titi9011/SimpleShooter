// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactMuzzleSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 3000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	bool GunTrace(FHitResult& OutHitResult, FVector& OutShotDirection);

	AController* GetOwnerController() const;

};
