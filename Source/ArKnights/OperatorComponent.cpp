#include "OperatorComponent.h"
#include "ArKnightsGameInstance.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

UOperatorComponent::UOperatorComponent()
{
	m_color.A = 1.f;
	SetSpriteColor(m_color);
}

void UOperatorComponent::UpdateAnimation()
{
	if (!m_life) return;

	CheckFrameEvent();
}

void UOperatorComponent::CheckFrameEvent()
{
	if (GetFlipbook() != nullptr && GetPlaybackPositionInFrames() == m_flipbooks[m_curState].frame)
	{
		switch (m_curState)
		{
		case EOperatorUnitFlipbook::Start: SetFlipbookState(EOperatorUnitFlipbook::Idle); break;
		case EOperatorUnitFlipbook::Start_Back: SetFlipbookState(EOperatorUnitFlipbook::Idle_Back); break;
		case EOperatorUnitFlipbook::Attack: 
		case EOperatorUnitFlipbook::Attack_Back:
		case EOperatorUnitFlipbook::Attack_Down: OnUnitAttackCallback.ExecuteIfBound(); break;
		case EOperatorUnitFlipbook::Die: 
		{
			m_life = false;
			FadeIn(false);
			BlackIn(true);
			SetPlayRate(0);
			break;
		}
		}
	}
}

EOperatorUnitFlipbook UOperatorComponent::GetCurFlipbookState() const
{
	return m_curState;
}

void UOperatorComponent::Start(EOperatorCode operatorCode)
{
	m_life = true;
	SetInitColor();
	SetPlayRate(1);

	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance) return;

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

	m_curState = EOperatorUnitFlipbook::Start;
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

void UOperatorComponent::SetFlipbookState(EOperatorUnitFlipbook unitState)
{
	if (m_curState != unitState)
	{
		m_curState = unitState;
		SetFlipbook(m_flipbooks[m_curState].Flipbook);
		SetFlipbookTransform(m_flipbooks[m_curState].X, m_flipbooks[m_curState].Y, m_flipbooks[m_curState].Z);
	}
}

void UOperatorComponent::RemoveFlipbookData()
{
	m_flipbooks.Empty();
}