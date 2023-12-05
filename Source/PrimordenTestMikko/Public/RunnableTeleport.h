// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "PrimordenTestMikko/Circle.h"
#include "HAL/Runnable.h"


/**
 * 
 */
class PRIMORDENTESTMIKKO_API RunnableTeleport : FRunnable
{
public:
	RunnableTeleport(TPromise<FVector>* Promise, ACircle* CirclePtr);
	virtual ~RunnableTeleport();

protected:

	bool bStop;
	FRunnableThread* Thread;
	class TPromise<FVector>* Promise;
	UPROPERTY()
	ACircle* CirclePtr;

public:

	virtual void Exit() override;
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	UFUNCTION()
	FVector2D GetViewportSize();

	UFUNCTION()
	FVector CalculateTeleport(TeleportCase Case);
};
