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
	//find open door class
	for (TObjectIterator<URotationOpenDoor> _itr; _itr; ++_itr)
	{
		if (_itr->IsA(URotationOpenDoor::StaticClass())) {
			_openDoor = *_itr;
		}
	}
}
///Func to find physics component
void UGrabber::FindPhysicsComponent()
{
	//checking for physics handle
	_physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();//get physics handler
	if (!_physicsHandler) {//check for it
		//if no print it
		UE_LOG(LogTemp, Error, TEXT("No Physics handler attached"));
	}
}
///Func to get Input handler
void UGrabber::FindInputHandler() {
	//checking for input handler and getting it
	_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (_inputComponent)
	{
		_inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);//get grab 
		_inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);//get release
	}
}
///Func to grab 
void UGrabber::Grab()
{
	FHitResult _hitResult = GetFirstPhysicsBody();//get hit result
	_componentToGrab = _hitResult.GetComponent();//get actor to grab

	_actorHit = _hitResult.GetActor();//get raycast actor hit

	_bGravity = false;//turn off gravity 
	if (_actorHit) //check for raycast actorhit
	{
		if (!_physicsHandler)//check for physisc handler
			return;
		_componentToGrab->SetEnableGravity(_bGravity);//disable gravity
		_physicsHandler->GrabComponentAtLocation//grab component
		(
			_componentToGrab, 
			NAME_None, 
			GetLineTraceEnd()
		);
	}
}

///Func to release
void UGrabber::Release()
{
	if (!_physicsHandler)
		return;
	_bGravity = true;
	if (!_componentToGrab)
		return;
	if (!_openDoor)
		return;
	_componentToGrab->SetEnableGravity(_bGravity);//turn on gravity
	_physicsHandler->ReleaseComponent();//release component

}
///Func to set number correctly rotated objects
void UGrabber::SetNumberOfDone() 
{
	if (!_physicsHandler)
		return;
	if (!_componentToGrab)
		return;
	if (!_openDoor)
		return;
	if (!_actorHit)
		return;
	if (_actorHit->GetActorRotation().Roll >= 70.f && _actorHit->GetActorRotation().Roll <= 120.f) //check for actor rotation
	{
		_openDoor->SetCurrent();//increase number
		printVar = _openDoor->GetCurrent();//get number
	}
	else 
	{
		UE_LOG(LogTemp, Log, TEXT("END"));
		printVar = _openDoor->GetCurrent();//get current number
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
		_physicsHandler->SetTargetLocation(GetLineTraceEnd());//move it 
		
	}
	
}
//Func to get actors physics component
FHitResult UGrabber::GetFirstPhysicsBody() const
{
	GetLineTraceEnd();//where line trace is ending

	FHitResult _hit;//hit actor
	//Ray-cast out to a certain distance(reach)
	FCollisionQueryParams _traceParams(FName(""), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(//get actor by object type
		_hit,
		GetPlayerWolrdPos(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		_traceParams
	);
	return _hit;//return actor
}
///Func to get player`s world position
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
///Func to get end of line trace
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