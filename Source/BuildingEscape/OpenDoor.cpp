// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Actor.h"
#define OUT
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
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	// ...
	FinalYaw += StartingYaw;
	PressurePlateLog();
	FindAudioComponent();
}
void UOpenDoor::PressurePlateLog()
{
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
	if (GetTotalMass() > MassThatOpens)
	{
		OpenTheDoor(DeltaTime);
		//door last opened = when the door was opened
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		//if the door has been open longer than x seconds close it
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorCloseDelay)
		{
			CloseTheDoor(DeltaTime);
		}
	}

}
void UOpenDoor::OpenTheDoor(float DeltaTime)
{
	DoorCloseSound = false;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, FinalYaw, DeltaTime, DoorOpenSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
	if (!MyAudioComponent)
	{
		return;
	}
	if (!DoorOpenSound)
	{
		MyAudioComponent->Play();
		DoorOpenSound = true;
	}
}
void UOpenDoor::CloseTheDoor(float DeltaTime)
{
	DoorOpenSound = false;
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, StartingYaw, DeltaTime, DoorCloseSpeed);
	GetOwner()->SetActorRotation(CurrentRotation);
	if (!MyAudioComponent)
	{
		return;
	}
	if (!DoorCloseSound)
	{
		MyAudioComponent->Play();
		DoorCloseSound = true;
	}
}
float UOpenDoor::GetTotalMass() const
{
	if (!PressurePlate)
	{
		return 0.f;
	}
	float TotalMass = 0.f;
	//Find all Overlapping Actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//Get total mass
	return TotalMass;
}
void UOpenDoor::FindAudioComponent()
{
	MyAudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!MyAudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component"), *GetOwner()->GetName());
	}
}