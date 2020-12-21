#include "EnemyComponent.h"
#include "ArKnightsGameInstance.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

UEnemyComponent::UEnemyComponent()
{
}

void UEnemyComponent::UpdateAnimation()
{
	CheckFrameEvent();
}

void UEnemyComponent::CheckFrameEvent()
{
	if (GetFlipbook() != nullptr && GetPlaybackPositionInFrames() == m_flipbooks[m_curState].frame)
	{
		switch (m_curState)
		{
		case EEnemyUnitFlipbook::Attack: break;
		case EEnemyUnitFlipbook::Die:
		{
			FadeIn(false);
			BlackIn(true);
			SetPlayRate(0);
			break;
		}
		}
	}
}

void UEnemyComponent::LoadFlipbookData(EEnemyCode enemyCode)\
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::EnemyFlipbookData)->GetRowNames().Num(); i++)
	{
		FEnemyFlipbookData* pFlipbookData = pGameInstance->GetDataTable(EGameDataTable::EnemyFlipbookData)->FindRow<FEnemyFlipbookData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (enemyCode == pFlipbookData->EnemyCode)
		{
			m_flipbooks.Add(pFlipbookData->FlipbookState);
			m_flipbooks[pFlipbookData->FlipbookState].frame = pFlipbookData->Frame;
			m_flipbooks[pFlipbookData->FlipbookState].X = pFlipbookData->X;
			m_flipbooks[pFlipbookData->FlipbookState].Y = pFlipbookData->Y;
			m_flipbooks[pFlipbookData->FlipbookState].Z = pFlipbookData->Z;
			m_flipbooks[pFlipbookData->FlipbookState].Flipbook = LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
		}
	}

	SetFlipbook(m_flipbooks[EEnemyUnitFlipbook::Idle].Flipbook);
}

void UEnemyComponent::SetFlipbookState(EEnemyUnitFlipbook unitState)
{
	if (m_curState != unitState)
	{
		m_curState = unitState;
		SetFlipbook(m_flipbooks[m_curState].Flipbook);
		SetComponentTransform();
	}
}

void UEnemyComponent::SetComponentTransform()
{
	FVector flipbookScale = FVector(0.35f);
	SetRelativeScale3D(flipbookScale);

	FRotator fliopbookRotation = FRotator(0, 270.0f, 80.0f);
	SetRelativeRotation(fliopbookRotation);

	FVector flipbookLocation = FVector(m_flipbooks[m_curState].X, -m_flipbooks[m_curState].Y, m_flipbooks[m_curState].Z);
	SetRelativeLocation(flipbookLocation);
}