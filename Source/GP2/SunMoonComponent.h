// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DayNightTriggerComponent.h"
#include "Math/Range.h"
#include "Misc/App.h"
#include "Curves/CurveFloat.h"
#include "Components/DirectionalLightComponent.h"
#include "SunMoonComponent.generated.h"

UENUM()
enum DayNight {
	CelestialDay UMETA(DisplayName = "Day State"),
	CelestialNight UMETA(DisplayName = "Day State"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP2_API USunMoonComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Components)
	UDayNightTriggerComponent* dayNightTriggerComponent;


public:
	UPROPERTY(EditAnywhere, Category = "Positioning")
		float distanceFromCenter = 500;
	UPROPERTY(EditAnywhere, Category = "Positioning")
		float sunActiveHeight = 100;
	UPROPERTY(EditAnywhere, Category = "Positioning")
		float moonActiveHeight = 100;
	UPROPERTY(EditAnywhere, Category = "Positioning")
		float inactiveHeight = -100;
	UPROPERTY(EditAnywhere, Category = "Positioning")
		UCurveFloat* heightCurve;

	UPROPERTY(EditAnywhere, Category = "Duration")
		float duration = 2;

		
	UPROPERTY(EditAnywhere, Category = "Light")
		float sunInactiveIntensity = 0;
	float sunActiveIntensity;
	UPROPERTY(EditAnywhere, Category = "Light")
		float moonInactiveIntensity = 0;
	float moonActiveIntensity;
	UPROPERTY(EditAnywhere, Category = "Light")
		UCurveFloat* intensityCurve;
		
	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor sunInactiveColor = sunActiveColor;
	FLinearColor sunActiveColor;
	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor moonInactiveColor = moonActiveColor;
	FLinearColor moonActiveColor;
	UPROPERTY(EditAnywhere, Category = "Color")
		UCurveFloat* colorCurve;
	
	

	bool toggle;

	UPROPERTY(EditAnywhere, Category = "Center Reference")
		AActor* center;
	APawn* playerCharacter;
	AActor* sun;
	AActor* moon;

private:

	TEnumAsByte<DayNight> dayOrNight;
	TArray<AActor*> celestialsArray;
	TArray<AActor*> lightArray;
	TArray<UDirectionalLightComponent*> dirLightArray;


	AActor* activeCelestial;
	AActor* sunLightActor;
	AActor* moonLightActor;

	UDirectionalLightComponent* sunDirLight;
	UDirectionalLightComponent* moonDirLight;

	float sunCurrentIntensity;
	float moonCurrentIntensity;
	float sunTargetIntensity;
	float moonTargetIntensity;
	float sunStartIntensity;
	float moonStartIntensity;

	float dayAngle = 0;
	float nightAngle = 180;
	float time = 0;

	float sunColorDuration;

	FRotator startRot;
	FRotator targetRot;
	FRotator dayRot;
	FRotator nightRot;

	FVector sunCurrentLocation;
	FVector sunTargetLocation;
	FVector moonTargetLocation;

	FLinearColor sunTargetColor;
	FLinearColor sunStartColor;
	FLinearColor moonTargetColor;
	FLinearColor moonStartColor;

	FVector activeTargetLocation;
	FVector inactiveTargetLocation;
	FVector sunStartLocation;
	FVector moonStartLocation;



	FVector vSunActiveHeight;
	FVector vMoonActiveHeight;
	FVector vInactiveHeight;

	bool bMoveCelestials = false;

public:	
	USunMoonComponent();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ToggleCelestials(int dayNight);
	void MoveCelestials(float DeltaTime, bool move);

};
