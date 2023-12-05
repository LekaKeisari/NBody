// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PrimordenTestMikko/Circle.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class PRIMORDENTESTMIKKO_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//This makes it possible to use a child blueprint of ACircle
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACircle> BP_CircleTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int Amount = 1000;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
