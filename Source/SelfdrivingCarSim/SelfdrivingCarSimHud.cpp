// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelfdrivingCarSimHud.h"
#include "SelfdrivingCarSimPawn.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

// Needed for VR Headset
#include "Engine.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

ASelfdrivingCarSimHud::ASelfdrivingCarSimHud()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}

void ASelfdrivingCarSimHud::DrawHUD()
{
	Super::DrawHUD();

	// Calculate ratio from 720p
	const float HUDXRatio = Canvas->SizeX / 1280.f;
	const float HUDYRatio = Canvas->SizeY / 720.f;

	bool bHMDDeviceActive = false;

	// We dont want the onscreen hud when using a HMD device	
#if HMD_MODULE_INCLUDED
	bHMDDeviceActive = GEngine->IsStereoscopic3D();
#endif // HMD_MODULE_INCLUDED
	if( bHMDDeviceActive == false )
	{
		// Get our vehicle so we can check if we are in car. If we are we don't want onscreen HUD
		ASelfdrivingCarSimPawn* Vehicle = Cast<ASelfdrivingCarSimPawn>(GetOwningPawn());
		if ((Vehicle != nullptr) && (Vehicle->bInCarCameraActive == false))
		{
			FVector2D ScaleVec(HUDYRatio * 1.4f, HUDYRatio * 1.4f);

			// Speed
			FCanvasTextItem SpeedTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 455), Vehicle->SpeedDisplayString, HUDFont, FLinearColor::FLinearColor(0.0f, 1.f, 0.0f,1.f));
			SpeedTextItem.Scale = ScaleVec;
			Canvas->DrawItem(SpeedTextItem);

			// Speed Error
			FCanvasTextItem SpeedErrorTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 545), Vehicle->SpeedErrorDisplayString, HUDFont, FLinearColor::Red);
			SpeedErrorTextItem.Scale = ScaleVec;
			Canvas->DrawItem(SpeedErrorTextItem);

			// Throttle
			FCanvasTextItem ThrottleTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 590), Vehicle->ThrottleDisplayString, HUDFont, FLinearColor::FLinearColor(0.0f, 1.f, 1.f));
			ThrottleTextItem.Scale = ScaleVec;
			Canvas->DrawItem(ThrottleTextItem);

			// Gear
			FCanvasTextItem GearTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 500.f), Vehicle->GearDisplayString, HUDFont, Vehicle->bInReverseGear == false ? Vehicle->GearDisplayColor : Vehicle->GearDisplayReverseColor);
			GearTextItem.Scale = ScaleVec;
			Canvas->DrawItem(GearTextItem);
		}
	}
}

#undef LOCTEXT_NAMESPACE
