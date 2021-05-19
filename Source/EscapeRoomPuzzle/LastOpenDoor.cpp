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
	//check if this door is last one
	if (_last == true)
	{
		//check for input string with hidden word
		if (!_textToOpen.Compare(_textFromUser))
		{
			OpenDoor(DeltaTime);//open door
			_doorLastOpened = GetWorld()->GetTimeSeconds();//get time when door opened
			_done = true;//game is over
		}

	}
	else
	{
		return;
	}
}
///Func to set string which gets from the user
void ULastOpenDoor::SetCurrentOpenDoorString(const FString _currentString)
{	
	_textFromUser = _currentString;
}
///Func to get string
FString ULastOpenDoor::ReturnTextToOpen() {
	return _textToOpen;
}