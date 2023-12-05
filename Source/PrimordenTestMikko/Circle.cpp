// Fill out your copyright notice in the Description page of Project Settings.

#include "Circle.h"
#include "HAL/Runnable.h"
#include "Async/Future.h"
#include "RunnableTeleport.h"

// Sets default values
ACircle::ACircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SetRootComponent(SpriteComponent);
		
}

void ACircle::BeginDestroy()
{
	if (TeleportRunnable)
	{
		delete TeleportRunnable;
		TeleportRunnable = nullptr;
	}
	
	Super::BeginDestroy();
}

// Called when the game starts or when spawned
void ACircle::BeginPlay()
{
	Super::BeginPlay();
	
	double DirectionX = FMath::RandRange(-1000, 1000);
	double DirectionZ = FMath::RandRange(-1000, 1000);

	Direction = FVector(DirectionX, 0, DirectionZ);
	Direction.Normalize();

}

// Called every frame
void ACircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement(DeltaTime);

	if (!WasRecentlyRendered(0.5f))
	{
		RunTeleportStep();
		//FVector2D ScreenLocation = FVector2D(0,0);
		//UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), GetActorLocation(), ScreenLocation, true);
		//

		//if (ScreenLocation.X > GetViewportSize().X)
		//{
		//	SetActorLocation(CalculateTeleport(TeleportCase::WidthMax), false, nullptr, ETeleportType::TeleportPhysics);
		//}
		//else if (ScreenLocation.X < 0)
		//{
		//	SetActorLocation(CalculateTeleport(TeleportCase::WidthMin));

		//}
		// if (ScreenLocation.Y > GetViewportSize().Y)
		//{
		//	SetActorLocation(CalculateTeleport(TeleportCase::HeightMax));

		//}
		//else if (ScreenLocation.Y < 0)
		//{
		//	SetActorLocation(CalculateTeleport(TeleportCase::HeightMin));
		//}
				
	}
}

void ACircle::HandleMovement(float DeltaTime) 
{
	FVector NewLocation = GetActorLocation() + Direction * Velocity * DeltaTime;
	
	SetActorLocation(NewLocation);
}



void ACircle::RunTeleportStep()
{
	TPromise<FVector>* Promise = new TPromise<FVector>();
	Promise->GetFuture().Next([this](FVector NewLocation)
		{
			// You should do something more interesting here
			this->SetActorLocation(NewLocation);
				//Promise = nullptr;
		});
	TeleportRunnable = new RunnableTeleport(Promise, this);
}