// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
// Sets default values
AExplosionEffect::AExplosionEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticle"));
	ExplosionAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionAudio"));

	ExplosionParticle->SetupAttachment(RootComponent);
	ExplosionAudio->SetupAttachment(ExplosionParticle);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ExplosionParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	static ConstructorHelpers::FObjectFinder<USoundBase>ExplosionAsset(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
}

// Called when the game starts or when spawned
void AExplosionEffect::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.5f);
}

// Called every frame
void AExplosionEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

