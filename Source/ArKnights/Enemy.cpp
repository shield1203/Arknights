#include "Enemy.h"
#include "ArKnightsGameInstance.h"

UEnemy::UEnemy()
{

}

void UEnemy::Initialize(EEnemyCode code)
{
	m_code = code;
	LoadEnemyData(code);
}

void UEnemy::LoadEnemyData(EEnemyCode code)
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	FEnemyData* pEnemyData = pGameInstance->GetDataTable(EGameDataTable::EnemyData)->FindRow<FEnemyData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(code)))), FString(""));

	m_name = pEnemyData->Name;
	m_maxHP = pEnemyData->MaxHP;
	m_atk = pEnemyData->ATK;
	m_speed = pEnemyData->Speed;
}

FString UEnemy::GetName() const
{
	return m_name;
}

float UEnemy::GetMaxHP() const
{
	return m_maxHP;
}

float UEnemy::GetAtk() const
{
	return m_atk;
}

float UEnemy::GetSpeed() const
{
	return m_speed;
}