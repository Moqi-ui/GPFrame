// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DoorActor.generated.h"

UCLASS()
class GPFRAME_API ADoorActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditInstanceOnly)
		UCurveFloat* DoorTimelineFloatCurve;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class ABossActor* BossActorReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UTimelineComponent* DoorTimelineComp;

	FOnTimelineFloat UpdateFunctionFloat;
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BossDiedEventFunction();
	//用于使用时间图表更新门相对位置的函数
	UFUNCTION()
		void UpdateTimelineComp(float Output);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
