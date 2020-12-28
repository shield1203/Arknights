#include "UnitComponent.h"
#include "TimerManager.h"
#include "PaperFlipbook.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"

UUnitComponent::UUnitComponent()
{
	SetReceivesDecals(false);
	m_color.R = 1.f;
	m_color.G = 1.f;
	m_color.B = 1.f;
	m_color.A = 0.f;
	SetSpriteColor(m_color);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SpriteMaterial(TEXT("MaterialInstanceConstant'/Paper2D/TranslucentUnlitSpriteMaterial.TranslucentUnlitSpriteMaterial'"));

	if (SpriteMaterial.Succeeded())
	{
		SetMaterial(0, SpriteMaterial.Object);
	}

	m_delegateChangeAlphaValue.BindDynamic(this, &UUnitComponent::ChangeAlphaValue);
	m_delegateChangeBlackValue.BindDynamic(this, &UUnitComponent::ChangeBlackValue);
	m_delegateChangeColorValue.BindDynamic(this, &UUnitComponent::ChangeColorValue);
}

void UUnitComponent::SetInitColor()
{
	m_color.R = 1.f;
	m_color.G = 1.f;
	m_color.B = 1.f;
	m_color.A = 1.f;
	SetSpriteColor(m_color);
}

void UUnitComponent::FadeIn(bool upAlphaValue)
{
	m_upAlphaValue = upAlphaValue;
	m_color.A = m_upAlphaValue ? 0.f : 1.f;
	
	GetWorld()->GetTimerManager().SetTimer(m_alphaTimerHandle, m_delegateChangeAlphaValue, 0.02, true);
}

void UUnitComponent::ChangeAlphaValue()
{	
	float fAlpha = m_color.A;

	m_upAlphaValue ? fAlpha += 0.02f : fAlpha -= 0.02f;

	m_color.A = fAlpha;

	SetSpriteColor(m_color);

	if (fAlpha <= 0 || fAlpha >= 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_alphaTimerHandle);
		if (fAlpha <= 0)
		{
			OnUnitDieCallback.ExecuteIfBound();
		}
	}
}

void UUnitComponent::BlackIn(bool upBlackValue)
{
	m_upBlackValue = upBlackValue;
	m_color.R = m_upBlackValue ? 1.f : 0.f;
	m_color.G = m_upBlackValue ? 1.f : 0.f;
	m_color.B = m_upBlackValue ? 1.f : 0.f;

	GetWorld()->GetTimerManager().SetTimer(m_blackTimerHandle, m_delegateChangeBlackValue, 0.04, true);
}

void UUnitComponent::ChangeBlackValue()
{
	float fColor = m_color.R;

	m_upBlackValue ? fColor -= 0.1f : fColor += 0.02f;

	m_color.R = fColor;
	m_color.G = fColor;
	m_color.B = fColor;

	SetSpriteColor(m_color);

	if (fColor <= 0 || fColor >= 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_blackTimerHandle);
	}
}

void UUnitComponent::UnitDamageColor()
{
	m_color.G = 0.f;
	m_color.B = 0.f;

	SetSpriteColor(m_color);

	if (!GetWorld()->GetTimerManager().IsTimerActive(m_damageColorTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(m_damageColorTimerHandle, m_delegateChangeColorValue, 0.02, true);
	}
}

void UUnitComponent::ChangeColorValue()
{
	m_color.G += 0.1f;
	m_color.B += 0.1f;

	SetSpriteColor(m_color);

	if (m_color.G >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_damageColorTimerHandle);
	}
}