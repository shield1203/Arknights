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
		UE_LOG(LogTemp, Warning, TEXT("Material Translucent"));
	}

	m_delegateChangeAlphaValue.BindDynamic(this, &UUnitComponent::ChangeAlphaValue);
}

void UUnitComponent::FadeIn(bool upAlphaValue)
{
	m_upValue = upAlphaValue;
	m_color.A = m_upValue ? 0.f : 1.f;
	
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