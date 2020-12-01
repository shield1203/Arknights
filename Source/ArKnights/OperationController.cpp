#include "OperationController.h"
#include "OperationSpectator.h"
#include "Engine/World.h"

AOperationController::AOperationController()
{
	bShowMouseCursor = true;
}

void AOperationController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (AOperationSpectator* MyPawn = Cast<AOperationSpectator>(GetPawn()))
	{
		if (MyPawn->IsPrepareUnitSetUp())
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			if (Hit.bBlockingHit)
			{
				MyPawn->SetPrepareUnitLocation(Hit.ImpactPoint);
			}
		}
	}
}

void AOperationController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectUnit", IE_Pressed, this, &AOperationController::OnUnitControllPressed);
	InputComponent->BindAction("SelectUnit", IE_Released, this, &AOperationController::OnUnitControllReleased);
}

void AOperationController::OnUnitControllPressed()
{
	
}

void AOperationController::OnUnitControllReleased()
{
	if (AOperationSpectator* MyPawn = Cast<AOperationSpectator>(GetPawn()))
	{
		MyPawn->FinishPrepareUnitSetUp();
	}
}