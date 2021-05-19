// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.h"
#include "MassOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPUZZLE_API UMassOpen : public UOpenDoor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMassOpen();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float MassOfActors() const;

private:
	//open with mass
	UPROPERTY(EditAnywhere)
		float _massToOpen = 30.f;//how many kg needs to open
	UPROPERTY(EditAnywhere)
		ATriggerVolume* _pressurePlate = nullptr;

};
