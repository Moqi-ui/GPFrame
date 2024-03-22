// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"


DECLARE_DELEGATE(FOnBossDiedDelegate)
DECLARE_MULTICAST_DELEGATE(FOnBossDiedDelegate2)
UCLASS()
class GPFRAME_API ABossActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

public:	
	// Sets default values for this actor's properties
	ABossActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	UFUNCTION()
		void HandleBossDiedEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FOnBossDiedDelegate OnBossDied;
	FOnBossDiedDelegate2 OnBossDiedMulti;
};
