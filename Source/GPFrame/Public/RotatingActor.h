// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class GPFRAME_API ARotatingActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class ABossActor* BossActor;

	
public:	
	// Sets default values for this actor's properties
	ARotatingActor();

	void SetbCanRotator(bool value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotatorActor();

	void BeginRotate();


	bool bCanRotator;

	const FQuat ActorRotationRate = (FQuat(FRotator(0, 2, 0)));

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
