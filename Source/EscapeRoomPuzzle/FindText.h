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
	class ULastOpenDoor* _openDoor;
private:
	UFUNCTION(BlueprintCallable, Category = "My Input Category")
	void OnInput(const FString input);
	UFUNCTION(BlueprintCallable, Category = "My Input Category")
	FString ReturnInput();
	UPROPERTY(EditAnywhere)
		FString _hiddenWord = "grandma";
		FString _input;
};
