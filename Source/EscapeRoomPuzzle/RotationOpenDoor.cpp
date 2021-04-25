// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationOpenDoor.h"

// Sets default values for this component's properties
URotationOpenDoor::URotationOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotationOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URotationOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (_numOfBags <= _current)
	{
		UE_LOG(LogTemp, Log, TEXT("Current"));
		OpenDoor(DeltaTime);
		_doorLastOpened = GetWorld()->GetTimeSeconds();
	}
}
float URotationOpenDoor::RotationOfActors() const
{
	return 0.0f;
}
int URotationOpenDoor::SetCurrent()
{
	return _current++;
}
int URotationOpenDoor::GetCurrent() {
	return _current;
}

