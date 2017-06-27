// Fill out your copyright notice in the Description page of Project Settings.

#include "SA_Afflicted.h"
#include "SA_AfflictedGameModeBase.h"
#include "MyHUD.h"

ASA_AfflictedGameModeBase::ASA_AfflictedGameModeBase() {
	HUDClass = AMyHUD::StaticClass();
}
