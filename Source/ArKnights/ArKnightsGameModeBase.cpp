#include "ArKnightsGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "SoundSystem.h"

AArKnightsGameModeBase::AArKnightsGameModeBase()
{
	m_soundSystem = CreateDefaultSubobject<USoundSystem>(TEXT("GameMode_SoundSystem"));
}

void AArKnightsGameModeBase::AddWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (nullptr != NewWidgetClass)
	{
		UUserWidget* pAddWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (pAddWidget)
		{
			pAddWidget->AddToViewport();
			m_widgets.Add(pAddWidget);
		}
	}
}

void AArKnightsGameModeBase::RemoveLastWidget()
{
	if (m_widgets.Num() <= 0) return;

	m_widgets[m_widgets.Num() - 1]->RemoveFromParent();
	m_widgets.RemoveAt(m_widgets.Num() - 1);
}