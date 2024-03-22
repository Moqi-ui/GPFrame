// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireEffect.generated.h"

UCLASS()
class GPFRAME_API AFireEffect : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
		UParticleSystemComponent* FireEffectComp;

	UPROPERTY(EditDefaultsOnly)
		UAudioComponent* AudioComp;

public:	
	// Sets default values for this actor's properties
	AFireEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
