#include "TipManager.h"
#include "ArKnights_Keys.h"
#include "Engine/Texture2D.h"
#include "Math/UnrealMathUtility.h"

UTipManager::UTipManager()
{
	m_tipDataTable = LoadObject<UDataTable>(this, data_table_keys::tip);
	m_maxTipNumber = m_tipDataTable->GetRowMap().Num() - 1;

	ChangeTipNumber();

	for (int index = 0; index <= m_maxTipNumber; index++)
	{
		FTipData* pTipData = m_tipDataTable->FindRow<FTipData>(FName(*(FString::FormatAsNumber(index))), FString(""));
		UTexture2D* pBackground = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pTipData->Background)));
		m_backgrounds.Add(pBackground);
	}
}

void UTipManager::ChangeTipNumber()
{
	m_tipNumber = FMath::RandRange(0, m_maxTipNumber);
}

UTexture2D* UTipManager::GetBackground() const
{
	return m_backgrounds[m_tipNumber];
}

FString UTipManager::GetName() const
{
	FTipData* pTipData = m_tipDataTable->FindRow<FTipData>(FName(*(FString::FormatAsNumber(m_tipNumber))), FString(""));
	return pTipData->Name;
}

FString UTipManager::GetTip() const
{
	FTipData* pTipData = m_tipDataTable->FindRow<FTipData>(FName(*(FString::FormatAsNumber(m_tipNumber))), FString(""));
	return pTipData->Tip;
}