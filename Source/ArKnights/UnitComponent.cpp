#include "UnitComponent.h"
#include "TimerManager.h"
#include "PaperFlipbook.h"

UUnitComponent::UUnitComponent()
{
	SetReceivesDecals(false);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SpriteMaterial(TEXT("MaterialInstanceConstant'/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial'"));

	if (SpriteMaterial.Succeeded())
	{
		SetMaterial(0, SpriteMaterial.Object);
	}

	m_delegateChangeAlphaValue.BindDynamic(this, &UUnitComponent::ChangeAlphaValue);
}

void UUnitComponent::FadeIn()
{
	m_upValue = true;
	m_color.A = 0.f;
	GetWorld()->GetTimerManager().SetTimer(m_alphaTimerHandle, m_delegateChangeAlphaValue, 0.02, true);
}

void UUnitComponent::FadeOut()
{
	m_upValue = false;
	m_color.A = 1.f;
	GetWorld()->GetTimerManager().SetTimer(m_alphaTimerHandle, m_delegateChangeAlphaValue, 0.02, true);
}

void UUnitComponent::ChangeAlphaValue()
{	
	float fAlpha = m_color.A;

	m_upValue ? fAlpha += 0.02f : fAlpha -= 0.02f;

	m_color.A = fAlpha;

	SetSpriteColor(m_color);

	if (fAlpha <= 0 || fAlpha >= 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_alphaTimerHandle);
	}
}