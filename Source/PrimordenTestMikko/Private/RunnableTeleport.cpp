// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnableTeleport.h"

RunnableTeleport::RunnableTeleport(TPromise<FVector>* Promise, ACircle* CirclePtr)
{
	this->Promise = Promise;
	this->CirclePtr = CirclePtr;
	Thread = FRunnableThread::Create(this, TEXT("Teleport"));
}

RunnableTeleport::~RunnableTeleport()
{
	if (Thread)
	{
		Thread->Kill();
		delete Thread;
	}
}
void RunnableTeleport::Exit()
{
	delete Promise;
	//UE_LOG(LogTemp, Warning, TEXT("Promise FINALLY deleted in RunnableTeleport::Exit()"));
}

bool RunnableTeleport::Init()
{
	bStop = false;
	return true;
}

uint32 RunnableTeleport::Run()
{
	//UE_LOG(LogTemp, Warning, TEXT("Running Teleport"))

		
			FVector2D ScreenLocation = FVector2D(0, 0);
			FVector NewLocation = FVector(0, 0, 0);
			UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(CirclePtr->GetWorld(), 0), CirclePtr->GetActorLocation(), ScreenLocation, true);


			if (ScreenLocation.X > GetViewportSize().X)
			{
				NewLocation = CalculateTeleport(TeleportCase::WidthMax);
			}
			else if (ScreenLocation.X < 0)
			{
				NewLocation = CalculateTeleport(TeleportCase::WidthMin);
			}
			if (ScreenLocation.Y > GetViewportSize().Y)
			{
				NewLocation = CalculateTeleport(TeleportCase::HeightMax);
			}
			else if (ScreenLocation.Y < 0)
			{
				NewLocation = CalculateTeleport(TeleportCase::HeightMin);
			}
			if (bStop)
			{
				UE_LOG(LogTemp, Warning, TEXT("Stopped Teleport"))
					Promise->SetValue(FVector(0, 0, 0));
				return 1;
			}
			Promise->SetValue(NewLocation);

	
	return 0;
}

void RunnableTeleport::Stop()
{
	bStop = true;
}
FVector2D RunnableTeleport::GetViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}

	return Result;
}

//Calculate the location on the other side of the screen
FVector RunnableTeleport::CalculateTeleport(TeleportCase Case)
{
	switch (Case)
	{
	case TeleportCase::HeightMin:

		return FVector(CirclePtr->GetActorLocation().X, 0, CirclePtr->GetActorLocation().Z - GetViewportSize().Y);

		break;
	case TeleportCase::HeightMax:

		return FVector(CirclePtr->GetActorLocation().X, 0, CirclePtr->GetActorLocation().Z + GetViewportSize().Y);

		break;
	case TeleportCase::WidthMin:

		return FVector(CirclePtr->GetActorLocation().X + GetViewportSize().X, 0, CirclePtr->GetActorLocation().Z);

		break;
	case TeleportCase::WidthMax:

		return FVector(CirclePtr->GetActorLocation().X - GetViewportSize().X, 0, CirclePtr->GetActorLocation().Z);

		break;
	default:

		return FVector(0, 0, 0);
		break;
	}
}