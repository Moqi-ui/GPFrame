// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GPFrameGameMode.generated.h"


UCLASS(minimalapi)
class AGPFrameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGPFrameGameMode();

public:

	//尝试生成玩家的Pawn。
	//RestartPlayer是GameModeBase类中已经存在的方法。它会尝试在FindPlayerStart返回的位置上生成玩家的Pawn。
	virtual void RestartPlayer(AController* NewPlayer) override;

protected:
	virtual void BeginPlay() override;

};



