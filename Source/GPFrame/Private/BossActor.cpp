// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"
// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoxComp1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp1->SetupAttachment(RootComponent);
	BoxComp1->SetBoxExtent(FVector(128, 128, 64));
	//BoxComp->SetVisibility(true);

}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABossActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	HandleBossDiedEvent();
}

void ABossActor::HandleBossDiedEvent()
{
	OnBossDied.ExecuteIfBound();

	OnBossDiedMulti.Broadcast();
}
