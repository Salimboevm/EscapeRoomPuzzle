// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	
	_bGravity = false;

	FindPhysicsComponent();

	FindInputHandler();

	for (TObjectIterator<URotationOpenDoor> _itr; _itr; ++_itr)
	{
		if (_itr->IsA(URotationOpenDoor::StaticClass())) {
			_openDoor = *_itr;
		}
	}
}
void UGrabber::FindPhysicsComponent()
{
	//checking for physics handle
	_physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!_physicsHandler) {
		UE_LOG(LogTemp, Error, TEXT("No Physics handler attached"));
	}
}
void UGrabber::FindInputHandler() {
	//checking for input handler and getting it
	_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (_inputComponent)
	{
		_inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		_inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		
	}
}
void UGrabber::Grab()
{
	FHitResult _hitResult = GetFirstPhysicsBody();
	_componentToGrab = _hitResult.GetComponent();

	_actorHit = _hitResult.GetActor();

	_bGravity = false;
	if (_actorHit) 
	{
		if (!_physicsHandler)
			return;
		_componentToGrab->SetEnableGravity(_bGravity);
		_physicsHandler->GrabComponentAtLocation
		(
			_componentToGrab, 
			NAME_None, 
			GetLineTraceEnd()
		);
	}
}


void UGrabber::Release()
{
	if (!_physicsHandler)
		return;
	_bGravity = true;
	if (!_componentToGrab)
		return;
	if (!_openDoor)
		return;
	_componentToGrab->SetEnableGravity(_bGravity);
	_physicsHandler->ReleaseComponent();

}
void UGrabber::SetNumberOfDone() 
{
	if (_actorHit->GetActorRotation().Roll >= 70.f && _actorHit->GetActorRotation().Roll <= 120.f) 
	{
		_openDoor->SetCurrent();
		printVar = _openDoor->GetCurrent();
	}
	else 
	{
		UE_LOG(LogTemp, Log, TEXT("END"));
		printVar = _openDoor->GetCurrent();
		return;
	}
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!_physicsHandler)
		return;
	if (_physicsHandler->GrabbedComponent) 
	{
		_physicsHandler->SetTargetLocation(GetLineTraceEnd());
		
	}
	
}

FHitResult UGrabber::GetFirstPhysicsBody() const
{
	GetLineTraceEnd();

	FHitResult _hit;
	//Ray-cast out to a certain distance(reach)
	FCollisionQueryParams _traceParams(FName(""), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		_hit,
		GetPlayerWolrdPos(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		_traceParams
	);
	return _hit;
}

FVector UGrabber::GetPlayerWolrdPos() const
{
	//Get PLyaer`s view point
	FVector _playerVievPointLocation;
	FRotator _playerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		_playerVievPointLocation,
		_playerViewPointRotation
	);
	return _playerVievPointLocation;
}

FVector UGrabber::GetLineTraceEnd() const
{
	//Get PLyaer`s view point
	FVector _playerVievPointLocation;
	FRotator _playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		_playerVievPointLocation,
		_playerViewPointRotation
	);

	return _playerVievPointLocation + _playerViewPointRotation.Vector() * _reach;
	
}