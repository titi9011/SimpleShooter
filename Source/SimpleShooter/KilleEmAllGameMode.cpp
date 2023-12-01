// Fill out your copyright notice in the Description page of Project Settings.


#include "KilleEmAllGameMode.h"
#include "SimpleShooterPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"



void AKilleEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        EndGame(false);
    }
    //For loop over ShooterAi in World:
    for (AShooterAIController* AIController: TActorRange<AShooterAIController>(GetWorld()))
    {
        bool bAIControllerIsDead = AIController->IsDead();

        if (!bAIControllerIsDead)
        {
            return;
        }
    }

    EndGame(true);

}



void AKilleEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller: TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
