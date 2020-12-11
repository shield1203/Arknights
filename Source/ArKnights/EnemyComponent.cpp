#include "EnemyComponent.h"
#include "ArKnightsGameInstance.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Engine/DataTable.h"
#include "OperatorComponent.h"

void UEnemyComponent::Init()
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->GetRowNames().Num(); i++)
	{
		FOperatorFlipbookData* pFlipbookData = pGameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->FindRow<FOperatorFlipbookData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (EOperatorCode::Hoshiguma == pFlipbookData->OperatorCode)
		{
			UPaperFlipbook* newFlipbook = LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
			m_flipbooks.Add(newFlipbook);
		}
	}


	SetFlipbook(m_flipbooks[2]);
}