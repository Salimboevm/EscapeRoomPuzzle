// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPUZZLE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float MassOfActors() const;
	float RotationOfActors() const;

private:
	//door opening components
	UPROPERTY(EditAnywhere)
	float _targetYaw = 0.0f;
	float _initialYaw = NULL;
	float _currentYaw = NULL;

	//open door components
	float _doorLastOpened = NULL;
	UPROPERTY(EditAnywhere)
	float _doorCloseDelay = .5f;
	UPROPERTY(EditAnywhere)
	float _doorOpenSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float _doorCloseSpeed = 2.f;

	//open with mass
	UPROPERTY(EditAnywhere)
	float _massToOpen = 30.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* _pressurePlate = nullptr;

	//open with rotation
	UPROPERTY(EditAnywhere)
	float _rotationOfActors = 0.0f;

};
