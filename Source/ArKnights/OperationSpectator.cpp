#include "OperationSpectator.h"
#include "OperatorUnit.h"

AOperationSpectator::AOperationSpectator()
{
}

bool AOperationSpectator::IsSelectedOperator(EOperatorCode operatorCode) const
{
	if (m_selectedOperatorButton && m_selectedOperator == operatorCode) return true;
	return false;
}

void AOperationSpectator::SetSelectOperator(EOperatorCode operatorCode)
{
	if (IsSelectedOperator(operatorCode))
	{
		m_selectedOperatorButton = false;
	}
	else
	{
		m_selectedOperatorButton = true;
		m_selectedOperator = operatorCode;
	}
}

bool AOperationSpectator::IsPrepareUnitSetUp() const
{
	return m_prepareUnitSetUp;
}

void AOperationSpectator::StartPrepareUnit(UOperator* operatorData)
{
	m_prepareUnitSetUp = true;
	
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator rotator;
		FVector SpawnLocation;

		m_prepareUnit = World->SpawnActor<AOperatorUnit>(SpawnLocation, rotator, SpawnParams);
		
		if (m_prepareUnit)
		{
			m_prepareUnit->Initialize();
			FRotator rotator1;
			rotator1.Yaw = 90.0f;
			//m_prepareUnit->AddActorLocalRotation(rotator1);
			UE_LOG(LogTemp, Warning, TEXT("Good"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Fail!!!!!!!!!!!!!"));
		}
	}
}

void AOperationSpectator::SetPrepareUnitLocation(const FVector DestLocation)
{
	if (m_prepareUnit == nullptr) return;

	m_prepareUnit->SetActorLocation(DestLocation);
}

void AOperationSpectator::FinishPrepareUnitSetUp()
{
	m_prepareUnitSetUp = false;
}