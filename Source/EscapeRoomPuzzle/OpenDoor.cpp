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
		
	if (GetWorld()->GetTimeSeconds() - _doorLastOpened > _doorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
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
