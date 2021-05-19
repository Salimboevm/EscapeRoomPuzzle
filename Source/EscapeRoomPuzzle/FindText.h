// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LastOpenDoor.h"
#include "FindText.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMPUZZLE_API UFindText : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFindText();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
	class ULastOpenDoor* _openDoor;//last open door class
private:
	UFUNCTION(BlueprintCallable, Category = "My Input Category")
	void OnInput(const FString input);//blueprint callable func
	UFUNCTION(BlueprintCallable, Category = "My Input Category")
	FString ReturnInput();//func to get input
	UPROPERTY(EditAnywhere)
		FString _hiddenWord = "you cannot escape from this house";//hidden word to open door
		FString _input;//input to send
};
