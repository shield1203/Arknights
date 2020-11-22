#include "LobbyGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "SoundSystem.h"
#include "ArKnightsGameInstance.h"
#include "ItemManager.h"
#include "UserDataManager.h"
#include "OperatorManager.h"

ALobbyGameMode::ALobbyGameMode()
{
	m_soundSystem->PlayBGM(ESound_BGM::Lobby);

	static ConstructorHelpers::FClassFinder<UUserWidget> LobbyWidget(TEXT("/Game/Widget/Lobby/WB_LobbyOptionButtons"));
	if (LobbyWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), LobbyWidget.Class);
	}
}

void ALobbyGameMode::StartPlay()
{
	Super::StartPlay();

	SetMainWidget();
	AddToViewSubWidgets();
	RequestLobbyData();
}

void ALobbyGameMode::RequestLobbyData()
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	pGameInstance->GetItemManager()->RequestItems();
	pGameInstance->GetUserDataManager()->RequestUserData();
	pGameInstance->GetOperatorManager()->RequestOperators();
	pGameInstance->GetOperatorManager()->RequestTeams();
}