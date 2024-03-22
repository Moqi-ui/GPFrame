// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "BossActor.h"
// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));

	DoorFrame->SetupAttachment(RootComponent);
	Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
	Door->SetRelativeLocation(FVector(0, 35, 0));

}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	//���������󶨵�UpdateTimelineComp���������
	UpdateFunctionFloat.BindDynamic(this, &ADoorActor::UpdateTimelineComp);
	
	//����и������ߣ�����ͼ��󶨵����ǵĸ��º���
	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}

	if (BossActorReference)
	{
		//BossActorReference->OnBossDied.BindUObject(this, &ADoorActor::BossDiedEventFunction);

		BossActorReference->OnBossDiedMulti.AddUObject(this, &ADoorActor::BossDiedEventFunction);
	}
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorActor::BossDiedEventFunction()
{
	DoorTimelineComp->Play();
}

void ADoorActor::UpdateTimelineComp(float Output)
{
	// ����ʱ�������ߵ�����������������ŵ������λ��
	FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
	Door->SetRelativeRotation(DoorNewRotation);
}