#include "EnemyManager.h"
#include "EngineUtils.h"
#include "EnemySpawnPlace.h"
#include "EnemyUnit.h"

UEnemyManager::UEnemyManager()
{

}

void UEnemyManager::LoadOperationEnemyData(int32 Episode, int32 Chapter)
{
	FString DataTablePath = TEXT("/Game/DataTable/OperationEnemy") + FString::FromInt(Episode) + TEXT("-") + FString::FromInt(Chapter);

	UDataTable* pDataTable = LoadObject<UDataTable>(this, *DataTablePath);

	if (pDataTable == nullptr) return;

	m_spawnIndex = 0;
	m_operationEnemyData.Empty();
	m_operationEnemyData.SetNum(pDataTable->GetRowNames().Num());
	for (int32 i = 0; i < pDataTable->GetRowNames().Num(); i++)
	{
		FOperationEnemyData* pOperationEnemyData = pDataTable->FindRow<FOperationEnemyData>(FName(*(FString::FormatAsNumber(i))), FString(""));

		m_operationEnemyData[i].EnemyCode = pOperationEnemyData->EnemyCode;
		m_operationEnemyData[i].SpawnPlace = pOperationEnemyData->SpawnPlace;
		m_operationEnemyData[i].SpawnTime = pOperationEnemyData->SpawnTime;
		m_operationEnemyData[i].DestinationXPos = pOperationEnemyData->DestinationXPos;
		m_operationEnemyData[i].DestinationYPos = pOperationEnemyData->DestinationYPos;
		m_operationEnemyData[i].HoldingTime = pOperationEnemyData->HoldingTime;
	}
}

TArray<EEnemyCode> UEnemyManager::GetOperationEnemy(int32 Episode, int32 Chapter)
{
	TArray<EEnemyCode> OperationEnemy;

	FString DataTablePath = TEXT("/Game/DataTable/OperationEnemy") + FString::FromInt(Episode) + TEXT("-") + FString::FromInt(Chapter);
	UDataTable* pDataTable = LoadObject<UDataTable>(this, *DataTablePath);

	if (pDataTable == nullptr) return OperationEnemy;

	for (int32 i = 0; i < pDataTable->GetRowNames().Num(); i++)
	{
		FOperationEnemyData* pOperationEnemyData = pDataTable->FindRow<FOperationEnemyData>(FName(*(FString::FormatAsNumber(i))), FString(""));

		if (!OperationEnemy.Contains(pOperationEnemyData->EnemyCode))
		{
			OperationEnemy.Add(pOperationEnemyData->EnemyCode);
		}
	}

	return OperationEnemy;
}

void UEnemyManager::OperationStart()
{
	
}

void UEnemyManager::CheckEnemySpawnTime(float deltaTime)
{
	if (m_operationEnemyData.Num() <= m_spawnIndex) return;

	m_second += deltaTime;
	if (m_operationEnemyData[m_spawnIndex].SpawnTime <= m_second)
	{
		m_second = 0;

		for (const auto& entity : TActorRange<AEnemySpawnPlace>(GetWorld()))
		{
			if (entity->GetPlaceNum() == m_operationEnemyData[m_spawnIndex].SpawnPlace)
			{
				entity->SpawnEnemy(m_operationEnemyData[m_spawnIndex].EnemyCode, m_operationEnemyData[m_spawnIndex].DestinationXPos, m_operationEnemyData[m_spawnIndex].DestinationYPos, m_operationEnemyData[m_spawnIndex].HoldingTime);
				m_spawnIndex++;
				return;
			}
		}
	}
}