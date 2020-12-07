#include "OperatorComponent.h"
#include "ArKnightsGameInstance.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

UOperatorComponent::UOperatorComponent()
{
}

void UOperatorComponent::Start(EOperatorCode operatorCode)
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
		if (operatorCode == pFlipbookData->OperatorCode)
		{
			m_flipbooks.Add(pFlipbookData->FlipbookState);
			m_flipbooks[pFlipbookData->FlipbookState].frame = pFlipbookData->Frame;
			m_flipbooks[pFlipbookData->FlipbookState].X = pFlipbookData->X;
			m_flipbooks[pFlipbookData->FlipbookState].Y = pFlipbookData->Y;
			m_flipbooks[pFlipbookData->FlipbookState].Z = pFlipbookData->Z;
			m_flipbooks[pFlipbookData->FlipbookState].Flipbook = LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
		}
	}

	m_curState = EOperatorUnitFlipbook::Idle;
	SetFlipbook(m_flipbooks[m_curState].Flipbook);
	SetFlipbookTransform(m_flipbooks[m_curState].X, m_flipbooks[m_curState].Y, m_flipbooks[m_curState].Z);
}

void UOperatorComponent::SetFlipbookTransform(float x, float y, float z)
{
	FVector flipbookScale = FVector(0.35f);
	SetRelativeScale3D(flipbookScale);

	FRotator fliopbookRotation = FRotator(0, 90.0f, -80.0f);
	SetRelativeRotation(fliopbookRotation);

	FVector flipbookLocation = FVector(x, y, z);
	SetRelativeLocation(flipbookLocation);
}

void UOperatorComponent::WithDraw()
{
	
}