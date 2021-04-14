// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPUZZLE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float _reach = 185.f;

	UInputComponent* _inputComponent = nullptr;
	UPhysicsHandleComponent* _physicsHandler = nullptr;
	void Grab();
	void Release();
	void FindPhysicsComponent();
	void FindInputHandler();

	//Get First Physics body in reach and return it
	FHitResult GetFirstPhysicsBody() const;
	//Get Line Trace End from player and return it
	FVector GetLineTraceEnd() const;
	//Get player position in the World
	FVector GetPlayerWolrdPos() const;
};
