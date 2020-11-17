#include "Operator.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "ArKnightsGameInstance.h"

UOperator::UOperator()
{

}

void UOperator::Initialize(EOperatorCode code, uint8 level)
{
	m_code = code;
	m_level = level;

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

FString UOperator::GetName() const
{
	return m_data.Name;
}

UTexture2D* UOperator::GetThumbnail() const
{
	return m_thumbnail;
}

EOperatorRarity UOperator::GetRarity() const
{
	return m_data.Rarity;
}

EOperatorClass UOperator::GetClass() const
{
	return m_data.Class;
}