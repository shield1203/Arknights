#include "Operator.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "ArKnightsGameInstance.h"

UOperator::UOperator()
{

}

void UOperator::Initialize(EOperatorCode code, int32 level, float curExp, int32 rank, int32 potentialAbility, int32 reliability)
{
	m_code = code;
	m_level = level;
	m_curExp = curExp;
	m_rank = rank;
	m_potentialAbility = potentialAbility;
	m_reliability = reliability;

	LoadOperatorData(m_code);
}

void UOperator::LoadOperatorData(EOperatorCode Operatorcode)
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	FOperatorData* pOperatorData = pGameInstance->GetDataTable(EGameDataTable::OperatorData)->FindRow<FOperatorData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(Operatorcode)))), FString(""));
	
	m_data.Name = pOperatorData->Name;
	m_data.Rarity = pOperatorData->Rarity;
	m_data.Class = pOperatorData->Class;
	m_data.Faction = pOperatorData->Faction;
	m_data.MaxHP = pOperatorData->MaxHP;
	m_data.ATK = pOperatorData->ATK;
	m_data.DEF = pOperatorData->DEF;
	m_data.RES = pOperatorData->RES;
	m_data.RDP = pOperatorData->RDP;
	m_data.DP = pOperatorData->DP;
	m_data.Block = pOperatorData->Block;
	m_data.ASPD = pOperatorData->ASPD;
	m_thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pOperatorData->Thumbnail)));
}

int32 UOperator::GetCode() const
{
	return static_cast<int32>(m_code);
}

int32 UOperator::GetLevel() const
{
	return m_level;
}

float UOperator::GetExpPercent()
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return 0;
	}

	FOperatorExpData* pExpData = pGameInstance->GetDataTable(EGameDataTable::OperatorExpData)->FindRow<FOperatorExpData>(FName(*(FString::FormatAsNumber(m_level))), FString(""));

	return m_curExp / pExpData->MaxExp;
}

int32 UOperator::GetRank() const
{
	return m_rank;
}

int32 UOperator::GetPotentialAbility() const
{
	return m_potentialAbility;
}

int32 UOperator::GetReliability() const
{
	return m_reliability;
}


FString UOperator::GetName() const
{
	return m_data.Name;
}

EOperatorRarity UOperator::GetRarity() const
{
	return m_data.Rarity;
}

EOperatorClass UOperator::GetClass() const
{
	return m_data.Class;
}

UTexture2D* UOperator::GetThumbnail() const
{
	return m_thumbnail;
}