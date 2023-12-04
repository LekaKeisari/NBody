// Fill out your copyright notice in the Description page of Project Settings.

#include "Circle.h"

// Sets default values
ACircle::ACircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SetRootComponent(SpriteComponent);
		
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
		FVector2D ScreenLocation = FVector2D(0,0);
		UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), GetActorLocation(), ScreenLocation, true);
		

		if (ScreenLocation.X > GetViewportSize().X)
		{
			SetActorLocation(CalculateTeleport(TeleportCase::WidthMax), false, nullptr, ETeleportType::TeleportPhysics);
		}
		else if (ScreenLocation.X < 0)
		{
			SetActorLocation(CalculateTeleport(TeleportCase::WidthMin));

		}
		 if (ScreenLocation.Y > GetViewportSize().Y)
		{
			SetActorLocation(CalculateTeleport(TeleportCase::HeightMax));

		}
		else if (ScreenLocation.Y < 0)
		{
			SetActorLocation(CalculateTeleport(TeleportCase::HeightMin));
		}
				
	}
}

void ACircle::HandleMovement(float DeltaTime) 
{
	FVector NewLocation = GetActorLocation() + Direction * Velocity * DeltaTime;
	
	SetActorLocation(NewLocation);
}

FVector2D ACircle::GetViewportSize() 
{
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}

	return Result;
}

//Calculate the location on the other side of the screen
FVector ACircle::CalculateTeleport(TeleportCase Case)
{
	switch (Case)
	{
	case TeleportCase::HeightMin:

		return FVector(GetActorLocation().X, 0, GetActorLocation().Z - GetViewportSize().Y);
		
		break;
	case TeleportCase::HeightMax:

		return FVector(GetActorLocation().X, 0, GetActorLocation().Z + GetViewportSize().Y);

		break;
	case TeleportCase::WidthMin:

		return FVector(GetActorLocation().X + GetViewportSize().X, 0, GetActorLocation().Z);

		break;
	case TeleportCase::WidthMax:

		return FVector(GetActorLocation().X - GetViewportSize().X, 0, GetActorLocation().Z);

		break;
	default:

		return FVector(0, 0, 0);
		break;
	}
}