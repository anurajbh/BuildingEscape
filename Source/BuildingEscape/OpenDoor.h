// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Runtime\Engine\Classes\Engine\TriggerVolume.h>
#include "Actor.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PressurePlateLog();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenTheDoor(float DeltaTime);

	void CloseTheDoor(float DeltaTime);

	void FindAudioComponent();

	float GetTotalMass() const;
private:
	UPROPERTY(EditAnywhere)
		float FinalYaw = 90.0f;
	UPROPERTY(EditAnywhere)
		float StartingYaw = 0.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	float DoorLastOpened = 0.0f;
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5f;
	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed = 2.0f;
	UPROPERTY(EditAnywhere)
		float MassThatOpens = 50.f;
	UPROPERTY()
		UAudioComponent* MyAudioComponent = nullptr;
	//tracks if sound has been played
	bool DoorOpenSound = false;
	bool DoorCloseSound = true;
};
