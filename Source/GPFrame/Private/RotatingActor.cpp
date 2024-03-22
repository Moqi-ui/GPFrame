// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"
#include "BossActor.h"

// Sets default values
ARotatingActor::ARotatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	bCanRotator = false;

}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (BossActor)
	{
		//BossActor->OnBossDied.BindUObject(this, &ARotatingActor::BeginRotate);

		BossActor->OnBossDiedMulti.AddUObject(this, &ARotatingActor::BeginRotate);
	}
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanRotator)
	{
		RotatorActor();
	}
}

void ARotatingActor::SetbCanRotator(bool value)
{
	bCanRotator = value;
}
void ARotatingActor::RotatorActor()
{
	AddActorLocalRotation(ActorRotationRate);
}
void ARotatingActor::BeginRotate()
{
	bCanRotator = true;
}