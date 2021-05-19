// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.h"
#include "RotationOpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPUZZLE_API URotationOpenDoor : public UOpenDoor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotationOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	int SetCurrent();//increase number of rotated objects 
	int GetCurrent();//return number of rotated objects
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float RotationOfActors() const;
private:
	const int _numOfBags = 4;//how many bags should be rotated
	//open with rotation
	UPROPERTY(EditAnywhere)
		float _rotationOfActors = 0.0f;

	UPROPERTY(EditAnywhere)
		int _current = NULL;//current number of bags rotated
};
