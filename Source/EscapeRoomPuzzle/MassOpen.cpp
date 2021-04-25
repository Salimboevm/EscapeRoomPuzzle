// Fill out your copyright notice in the Description page of Project Settings.


#include "MassOpen.h"

// Sets default values for this component's properties
UMassOpen::UMassOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMassOpen::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMassOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (MassOfActors() > _massToOpen)
	{
		OpenDoor(DeltaTime);
		_doorLastOpened = GetWorld()->GetTimeSeconds();
	}
}

float UMassOpen::MassOfActors() const
{
	float _mass = 0.f;

	//Find all overlaping actors
	TArray<AActor*> _overlapingActors;
	if (!_pressurePlate)
		return _mass;
	_pressurePlate->GetOverlappingActors(_overlapingActors);

	//Add up their masses
	for (AActor* _actor : _overlapingActors)
	{
		_mass += _actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return _mass;
}
