// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

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

	_initialYaw = GetOwner()->GetActorRotation().Yaw;
	_currentYaw = _initialYaw;
	_targetYaw += _initialYaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MassOfActors()> _massToOpen)
	{
		OpenDoor(DeltaTime);
		_doorLastOpened = GetWorld()->GetTimeSeconds();

	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - _doorLastOpened > _doorCloseDelay) 
		{
			CloseDoor(DeltaTime);
		}
	}
	

	//FRotator OpenDoor(0.f, targetYaw, 0.f);
	//OpenDoor.Yaw = FMath::FInterpConstantTo(currentYaw, targetYaw, DeltaTime, 30);
	//GetOwner()->SetActorRotation(OpenDoor);
	// ...
}
void UOpenDoor::OpenDoor(float DeltaTime) {
	_currentYaw = FMath::Lerp(_currentYaw, _targetYaw, DeltaTime * _doorOpenSpeed);
	FRotator _doorRotation = GetOwner()->GetActorRotation();
	_doorRotation.Yaw = _currentYaw;
	GetOwner()->SetActorRotation(_doorRotation);
}
void UOpenDoor::CloseDoor(float DeltaTime) {
	_currentYaw = FMath::Lerp(_currentYaw, _initialYaw, DeltaTime * _doorCloseSpeed);
	FRotator _doorRotation = GetOwner()->GetActorRotation();
	_doorRotation.Yaw = _currentYaw;
	GetOwner()->SetActorRotation(_doorRotation);
}
float UOpenDoor::MassOfActors() const 
{
	float _mass = 0.f;

	//Find all overlaping actors
	TArray<AActor*> _overlapingActors;
	if (!_pressurePlate)
		return _mass;
	_pressurePlate->GetOverlappingActors(_overlapingActors);

	//Add up their masses
	for (AActor* _actor: _overlapingActors)
	{
		_mass += _actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return _mass;
}

float UOpenDoor::RotationOfActors() const
{
	return 0.0f;
}

