// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Property Includes
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"

#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TeleportCases.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Circle.generated.h"

UCLASS()
class PRIMORDENTESTMIKKO_API ACircle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACircle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Properties")
	FVector Direction = FVector(0.0f, 0.0f, 0.0f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Properties")
	float Velocity = 100.0f;

	UFUNCTION()
	void HandleMovement(float DeltaTime);

	class RunnableTeleport* TeleportRunnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprites")
	class UPaperSpriteComponent* SpriteComponent;

public:	

	virtual void BeginDestroy() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	UFUNCTION()
	virtual void RunTeleportStep();
};
