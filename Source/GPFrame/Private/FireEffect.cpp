// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AFireEffect::AFireEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireEffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireEffectComp"));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));

	FireEffectComp->SetupAttachment(RootComponent);

	AudioComp->SetupAttachment(FireEffectComp);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	static ConstructorHelpers::FObjectFinder<USoundBase>AudioAsset(TEXT("SoundCue'/Game/StarterContent/Audio/Fire01_Cue.Fire01_Cue'"));

	FireEffectComp->SetTemplate(ParticleAsset.Object);
	AudioComp->SetSound(AudioAsset.Object);
}

// Called when the game starts or when spawned
void AFireEffect::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.5f);
}

// Called every frame
void AFireEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

