// Fill out your copyright notice in the Description page of Project Settings.


#include "FireActor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "../GPFrameCharacter.h"

// Sets default values
AFireActor::AFireActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompont"));
	FireParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticle"));

	BoxComp->SetupAttachment(RootComponent);
	FireParticleComp->SetupAttachment(BoxComp);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>FireParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));

	FireParticleComp->SetTemplate(FireParticleAsset.Object);

	//BoxComp->SetBoxExtent(FVector());
}

// Called when the game starts or when spawned
void AFireActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AGPFrameCharacter* GPFrameCharacter = Cast<AGPFrameCharacter>(OtherActor);
	if (GPFrameCharacter)
	{
		GPFrameCharacter->IgniteFireTimer();
	}
}
void AFireActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	AGPFrameCharacter* GPFrameCharacter = Cast<AGPFrameCharacter>(OtherActor);
	if (GPFrameCharacter)
	{
		GPFrameCharacter->ClearFireTimer();
	}
}
