// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Runtime\Engine\Classes\Engine\TriggerVolume.h>
#include "Actor.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeDoor(float TargetYaw, float DeltaTime, float DoorSpeed);

	float GetTotalMass() const;
private:
	UPROPERTY(EditAnywhere)
	float FinalYaw = 90.0f;
	UPROPERTY(EditAnywhere)
	float StartingYaw = 0.0f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	float DoorLastOpened = 0.0f;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;
	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.0f;
	UPROPERTY(EditAnywhere)
	float MassThatOpens = 50.f;
};
