// Copyright Epic Games, Inc. All Rights Reserved.

#include "GPFrameGameMode.h"
#include "GPFrameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGPFrameGameMode::AGPFrameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGPFrameGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);


	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "RestartPlayer");
}
void AGPFrameGameMode::BeginPlay()
{

}
