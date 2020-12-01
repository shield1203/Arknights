#include "OperationSpectator.h"
#include "PlacementUnitActor.h"

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

		m_placementUnit = World->SpawnActor<APlacementUnitActor>(FVector(), FRotator(), SpawnParams);

		if (m_placementUnit)
		{
			m_placementUnit->Initialize(m_selectedOperator);
		}
	}
}

void AOperationSpectator::SetPrepareUnitLocation(const FVector DestLocation)
{
	if (m_placementUnit == nullptr) return;

	m_placementUnit->SetActorLocation(DestLocation);
}

void AOperationSpectator::FinishPrepareUnitSetUp()
{
	m_prepareUnitSetUp = false;

	m_placementUnit->Destroy();
	m_placementUnit = nullptr;
}