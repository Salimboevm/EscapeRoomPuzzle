// Fill out your copyright notice in the Description page of Project Settings.


#include "LastOpenDoor.h"

// Sets default values for this component's properties
ULastOpenDoor::ULastOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULastOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULastOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (_last == true)
	{

		if (!_textToOpen.Compare(_textFromUser))
		{
			OpenDoor(DeltaTime);
			_doorLastOpened = GetWorld()->GetTimeSeconds();
			_done = true;
		}

	}
	else
	{
		return;
	}
}
void ULastOpenDoor::SetCurrentOpenDoorString(const FString _currentString)
{	
	_textFromUser = _currentString;
}
FString ULastOpenDoor::ReturnTextToOpen() {
	return _textToOpen;
}