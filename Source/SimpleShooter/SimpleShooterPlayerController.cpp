// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterPlayerController.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void ASimpleShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    CrossScreen = CreateWidget(this, CrossClass);
    if (CrossScreen)
    {
        CrossScreen->AddToViewport();
    }
}



void ASimpleShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if(bIsWinner)
    {
        UE_LOG(LogTemp, Warning, TEXT("bIsWinner"));
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        CrossScreen->RemoveFromParent();
        WinScreen->AddToViewport();
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        CrossScreen->RemoveFromParent();
        LoseScreen->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

}