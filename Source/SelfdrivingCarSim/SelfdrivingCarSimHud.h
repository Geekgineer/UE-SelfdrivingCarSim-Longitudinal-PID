// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SelfdrivingCarSimHud.generated.h"

UCLASS(config = Game)
class ASelfdrivingCarSimHud : public AHUD
{
	GENERATED_BODY()

public:
	ASelfdrivingCarSimHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
