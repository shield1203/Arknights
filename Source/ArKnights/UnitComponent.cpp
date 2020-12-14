#include "UnitComponent.h"
#include "TimerManager.h"

UUnitComponent::UUnitComponent()
{
	SetReceivesDecals(false);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SpriteMaterial(TEXT("MaterialInstanceConstant'/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial'"));

	if (SpriteMaterial.Succeeded())
	{
		SetMaterial(0, SpriteMaterial.Object);
	}
}

void UUnitComponent::FadeIn()
{
	m_preAlphaValue = 0;
	m_nextAlphaValue = 1;
	//GetWorld()->GetTimerManager().SetTimer(m_changeAlphaTimerHandle, this, &UUnitComponent::ChangeAlphaValue, 0.02, true);
}

void UUnitComponent::FadeOut()
{

}

void UUnitComponent::ChangeAlphaValue()
{
	FVector defaultColor = FVector(1.f);

	m_preAlphaValue += 0.02f;

	if (m_preAlphaValue == m_nextAlphaValue)
	{

	}
}