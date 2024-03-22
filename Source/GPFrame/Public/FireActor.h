// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireActor.generated.h"

UCLASS()
class GPFRAME_API AFireActor : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* FireParticleComp;

public:	
	// Sets default values for this actor's properties
	AFireActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
