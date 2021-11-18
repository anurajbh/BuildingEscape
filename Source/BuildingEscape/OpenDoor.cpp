// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Actor.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	// ...
	FinalYaw += StartingYaw;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component but no pressure plate associated with it"), *GetOwner()->GetName());
	}
}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		ChangeDoor(FinalYaw, DeltaTime, DoorOpenSpeed);
		//door last opened = when the door was opened
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		//if the door has been open longer than x seconds close it
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorCloseDelay)
		{
			ChangeDoor(StartingYaw, DeltaTime, DoorCloseSpeed);
		}
	}
	
}

void UOpenDoor::ChangeDoor(float TargetYaw, float DeltaTime, float DoorSpeed)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, DoorSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
}
