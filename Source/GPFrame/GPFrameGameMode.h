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

	//����������ҵ�Pawn��
	//RestartPlayer��GameModeBase�����Ѿ����ڵķ��������᳢����FindPlayerStart���ص�λ����������ҵ�Pawn��
	virtual void RestartPlayer(AController* NewPlayer) override;

protected:
	virtual void BeginPlay() override;

};



