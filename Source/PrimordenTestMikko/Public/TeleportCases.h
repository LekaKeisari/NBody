// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TeleportCases.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
    enum class TeleportCase : uint8 {
    HeightMin = 0,
    HeightMax = 1,
    WidthMin = 2,
    WidthMax = 3
    }
;
