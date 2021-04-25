// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "FindText.h"

// Sets default values for this component's properties
UFindText::UFindText()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFindText::BeginPlay()
{
	Super::BeginPlay();

	for (TObjectIterator<ULastOpenDoor> _itr; _itr; ++_itr)
	{
		if (_itr->IsA(ULastOpenDoor::StaticClass())) {
			_openDoor = *_itr;
		}
	}
	// ...
}

void UFindText::OnInput(const FString input)
{
	_input = input;
	if (_input == _hiddenWord) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Working On Input"));
		_openDoor->SetCurrentOpenDoorString(input);
	}
}

FString UFindText::ReturnInput() {
	return _input;
}

// Called every frame
void UFindText::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

