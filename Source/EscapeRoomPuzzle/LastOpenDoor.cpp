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
		UE_LOG(LogTemp, Log, TEXT("Current case 3 word: %s"), *_textFromUser);
		if (!_textFromUser.Compare(_textToOpen))
		{
			UE_LOG(LogTemp, Warning, TEXT("Working"));
			UE_LOG(LogTemp, Warning, TEXT("Working"));
			OpenDoor(DeltaTime);
			_doorLastOpened = GetWorld()->GetTimeSeconds();
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
	UE_LOG(LogTemp, Warning, TEXT("Setted: %s"), *_textFromUser);
	UE_LOG(LogTemp, Warning, TEXT("Hidden: %s"), *_textToOpen);
}
