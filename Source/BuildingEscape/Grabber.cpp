// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Grabber.h"
#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	BindGrabberInputComponent();
	// ...
	//if (MyInputComponent)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%s has input component"), *GetOwner()->GetName());
	//}
}

void UGrabber::FindPhysicsHandle()
{
	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!MyPhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Physics Handle component"), *GetOwner()->GetName());
	}
	else
	{

	}
}
void UGrabber::BindGrabberInputComponent()
{
	MyInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	MyInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	MyInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UGrabber::Grab()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT MyPosition, OUT MyRotation);
	FVector DebugLineEnd = MyPosition + (Reach * MyRotation.Vector());
	FHitResult RaycastHit;
	FCollisionQueryParams QueryParams
	{
		FName(TEXT("")), false, GetOwner()
	};
	//raycast
	GetWorld()->LineTraceSingleByObjectType(OUT RaycastHit, MyPosition, DebugLineEnd, ECC_PhysicsBody, QueryParams);
	ActorHit = RaycastHit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabbed %s"), *ActorHit->GetName());
		//grab physics handle of the Actor
	}
}
void UGrabber::Release()
{
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Released %s"), *ActorHit->GetName());
		//release physics handle of the Actor
	}
}
