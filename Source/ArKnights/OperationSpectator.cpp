#include "OperationSpectator.h"
#include "PlacementUnitActor.h"
#include "TowerBlock.h"

AOperationSpectator::AOperationSpectator()
{
}

bool AOperationSpectator::IsSelectedOperator(EOperatorCode operatorCode) const
{
	if (m_selectedOperatorButton && m_selectedOperatorCode == operatorCode) return true;
	return false;
}

void AOperationSpectator::SetSelectOperator(EOperatorCode operatorCode, EOperatorClass operatorClass)
{
	if (IsSelectedOperator(operatorCode))
	{
		m_selectedOperatorButton = false;
	}
	else
	{
		m_selectedOperatorButton = true;
		m_selectedOperatorCode = operatorCode;
		m_selectedOperatorClass = operatorClass;
	}
}

EOperatorClass AOperationSpectator::GetSelectedOperatorClass()
{
	return m_selectedOperatorClass;
}

bool AOperationSpectator::IsSelectedOperatorButton() const
{
	return m_selectedOperatorButton;
}

bool AOperationSpectator::IsPrepareUnitSetUp() const
{
	return m_prepareUnitSetUp;
}

bool AOperationSpectator::IsPlacementOperator(EOperatorCode operatorCode)
{
	return m_placementOperators.Contains(operatorCode);
}

void AOperationSpectator::StartPrepareUnit(UOperator* operatorData)
{
	if (m_placementUnitActor != nullptr) return;

	m_prepareUnitSetUp = true;
	
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		m_placementUnitActor = World->SpawnActor<APlacementUnitActor>(FVector(), FRotator(0, 0, 0), SpawnParams);

		if (m_placementUnitActor)
		{

			m_placementUnitActor->Initialize(operatorData);
		}
	}
}

void AOperationSpectator::SetPrepareUnitLocation(FVector DestLocation, bool onTowerBlock)
{
	if (m_placementUnitActor == nullptr) return;

	m_placementUnitActor->SetUnitLocation(DestLocation, onTowerBlock);
}

void AOperationSpectator::FinishPrepareUnitSetUp(ATowerBlock* towerBlock)
{
	m_prepareUnitSetUp = false;

	if (towerBlock != nullptr && towerBlock->CanPlacement(m_selectedOperatorClass))
	{
		towerBlock->StartPlacement(m_placementUnitActor->GetOperatorData());
		m_placementOperators.Add(m_selectedOperatorCode);
		m_selectedOperatorButton = false;
	}

	if (m_placementUnitActor != nullptr)
	{
		m_placementUnitActor->Destroy();
		m_placementUnitActor = nullptr;
	}
}

void AOperationSpectator::AddPlacementOperator(EOperatorCode operatorCode)
{
	m_placementOperators.Add(operatorCode);
}

void AOperationSpectator::RemovePlacementOperator(EOperatorCode operatorCode)
{
	m_placementOperators.Remove(operatorCode);
}