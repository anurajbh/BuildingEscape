// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
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
	//physics handle component is used to interact with physics bodies
	FindPhysicsHandle();
	BindGrabberInputComponent();
	// ...
}

void UGrabber::FindPhysicsHandle()
{
	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//null check
	if (!MyPhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Physics Handle component"), *GetOwner()->GetName());
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
	if (!MyPhysicsHandle)
	{
		return;
	}
	//check if component grabbed
	if (MyPhysicsHandle->GrabbedComponent)
	{
		//modify transform location of component
		MyPhysicsHandle->SetTargetLocation(GetPlayerReachVector());
	}
	// ...
}
void UGrabber::Grab()
{
	if (!MyPhysicsHandle)
	{
		return;
	}
	FHitResult RaycastHit = GetFirstPhysicsActorInReach();
	UPrimitiveComponent* MyPrimitiveComponent = RaycastHit.GetComponent();
	ActorHit = RaycastHit.GetActor();
	//null check
	if (ActorHit)
	{
		//grab the component of the physics body
		MyPhysicsHandle->GrabComponentAtLocation(MyPrimitiveComponent, NAME_None, GetPlayerReachVector());

	}
}
//create a Raycast within Reach distance to return the first physics body it intersects, to indicate an interactable actor
FHitResult UGrabber::GetFirstPhysicsActorInReach()
{
	FHitResult RaycastHit;
	FVector RayCastLineEnd = GetPlayerReachVector();
	FCollisionQueryParams QueryParams
	{
		FName(TEXT("")), false, GetOwner()
	};
	//raycast
	GetWorld()->LineTraceSingleByObjectType(OUT RaycastHit, MyPosition, RayCastLineEnd, ECC_PhysicsBody, QueryParams);
	return RaycastHit;
}
void UGrabber::Release()
{
	if (!MyPhysicsHandle)
	{
		return;
	}
	//null check
	if (ActorHit)
	{
		//release physics handle of the Actor
		MyPhysicsHandle->ReleaseComponent();
	}
}
FVector UGrabber::GetPlayerReachVector()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT MyPosition, OUT MyRotation);
	//SumOfTwoVectors = PositionVector + RotationUnitVector*Reach
	return (MyPosition + (Reach * MyRotation.Vector()));
}
