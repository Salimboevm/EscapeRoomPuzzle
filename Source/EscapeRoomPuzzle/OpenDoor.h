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


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor(float DeltaTime);//func to open door
	void CloseDoor(float DeltaTime);//func to close door

	float _doorLastOpened = NULL;//time when door opened
	UOpenDoor();


private:
	//door opening components
	UPROPERTY(EditAnywhere)
	float _targetYaw = 0.0f;
	float _initialYaw = NULL;
	float _currentYaw = NULL;

	//open door components
	UPROPERTY(EditAnywhere)
	float _doorCloseDelay = .5f;//closing delay
	UPROPERTY(EditAnywhere)
	float _doorOpenSpeed = 1.f;//opening speed
	UPROPERTY(EditAnywhere)
	float _doorCloseSpeed = 2.f;//closing speed
};
