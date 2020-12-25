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
	m_boxLocationX = pEnemyData->BoxLocationX;
	m_boxWidth = pEnemyData->BoxWidth;
	m_boxHeight = pEnemyData->BoxHeight;
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

float UEnemy::GetBoxLocationX() const
{
	return m_boxLocationX;
}

float UEnemy::GetBoxWidth() const
{
	return m_boxWidth;
}

float UEnemy::GetBoxHeight() const
{
	return m_boxHeight;
}