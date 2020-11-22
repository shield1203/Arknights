#include "ArKnightsGameModeBase.h"
#include "ArknightsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "SoundSystem.h"
#include "WidgetManager.h"

AArKnightsGameModeBase::AArKnightsGameModeBase()
{
	m_soundSystem = CreateDefaultSubobject<USoundSystem>(TEXT("GameMode_SoundSystem"));
}

void AArKnightsGameModeBase::SetMainWidget()
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	pGameInstance->GetWidgetManager()->SetMainWidget(m_mainWidget);
}

void AArKnightsGameModeBase::AddToViewSubWidgets()
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	pGameInstance->GetWidgetManager()->AddToViewportSubWidgets();
}