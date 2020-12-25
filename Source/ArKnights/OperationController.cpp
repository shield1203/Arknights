#include "OperationController.h"
#include "OperationSpectator.h"
#include "TowerBlock.h"
#include "Engine/World.h"

AOperationController::AOperationController()
{
	bShowMouseCursor = true;
}

void AOperationController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	AOperationSpectator* MyPawn = Cast<AOperationSpectator>(GetPawn());
	if (MyPawn && MyPawn->IsPrepareUnitSetUp())
	{
		GetHitResultUnderFinger(m_touchIndex, ECC_Visibility, false, m_hit);

		if (m_hit.bBlockingHit)
		{
			ATowerBlock* pTowerBlock = Cast<ATowerBlock>(m_hit.Actor);
			FVector locationVector;

			if (pTowerBlock && pTowerBlock->CanPlacement(MyPawn->GetSelectedOperatorClass()))
			{
				locationVector = pTowerBlock->GetActorLocation();
				MyPawn->SetPrepareUnitLocation(locationVector, true);
			}
			else
			{
				locationVector = m_hit.ImpactPoint;
				locationVector.Z -= 50.0f;
				MyPawn->SetPrepareUnitLocation(locationVector);
			}
		}
	}
}

void AOperationController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("SelectUnit", IE_Pressed, this, &AOperationController::OnUnitControllPressed);
	//InputComponent->BindAction("SelectUnit", IE_Released, this, &AOperationController::OnUnitControllReleased);

	InputComponent->BindTouch(IE_Pressed, this, &AOperationController::OnUnitControllPressed);
	InputComponent->BindTouch(IE_Released, this, &AOperationController::OnUnitControllReleased);
}

void AOperationController::OnUnitControllPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	m_touchIndex = FingerIndex;
}

void AOperationController::OnUnitControllReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	AOperationSpectator* MyPawn = Cast<AOperationSpectator>(GetPawn());
	if (MyPawn)
	{
		ATowerBlock* pTowerBlock = nullptr;
		if (m_hit.bBlockingHit)
		{
			pTowerBlock = Cast<ATowerBlock>(m_hit.Actor);
		}

		MyPawn->FinishPrepareUnitSetUp(pTowerBlock);
	}
}