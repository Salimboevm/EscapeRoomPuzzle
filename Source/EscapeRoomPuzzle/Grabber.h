// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "RotationOpenDoor.h"
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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		AActor* _actorHit = nullptr;//actor hit 
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int printVar = 0;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class URotationOpenDoor* _openDoor;//open door class

	float _reach = 150.f;// max distance 

	bool _bGravity = false;

	UInputComponent* _inputComponent = nullptr;
	UPhysicsHandleComponent* _physicsHandler = nullptr;
	UFUNCTION(BlueprintCallable, Category = "Grab")
	void Grab();
	UFUNCTION(BlueprintCallable, Category = "Grab")
	void Release();
	UFUNCTION(BlueprintCallable, Category = "Grab")
	void SetNumberOfDone();
	void FindPhysicsComponent();
	void FindInputHandler();

	//Get First Physics body in reach and return it
	FHitResult GetFirstPhysicsBody() const;
	//Get Line Trace End from player and return it
	FVector GetLineTraceEnd() const;
	//Get player position in the World
	FVector GetPlayerWolrdPos() const;
	UPrimitiveComponent* _componentToGrab = nullptr;
};
