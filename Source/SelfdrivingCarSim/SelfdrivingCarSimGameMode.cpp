// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelfdrivingCarSimGameMode.h"
#include "SelfdrivingCarSimPawn.h"
#include "SelfdrivingCarSimHud.h"

ASelfdrivingCarSimGameMode::ASelfdrivingCarSimGameMode()
{
	DefaultPawnClass = ASelfdrivingCarSimPawn::StaticClass();
	HUDClass = ASelfdrivingCarSimHud::StaticClass();
}
