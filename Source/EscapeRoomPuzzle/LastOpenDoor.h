// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.h"
#include "LastOpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPUZZLE_API ULastOpenDoor : public UOpenDoor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULastOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetCurrentOpenDoorString(const FString _currentString);
	FString ReturnTextToOpen();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool _done = NULL;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	const FString _textToOpen = "grandma";
	UPROPERTY(EditAnywhere)
	FString _textFromUser;
	UPROPERTY(EditAnywhere)
	bool _last = NULL;	

};
