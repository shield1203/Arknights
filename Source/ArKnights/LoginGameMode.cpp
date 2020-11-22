#include "LoginGameMode.h"
#include "ArKnights_Keys.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "SoundSystem.h"
#include "SaveLoginData.h"
#include "Kismet/GameplayStatics.h"

ALoginGameMode::ALoginGameMode()
{
	m_soundSystem->PlayBGM(ESound_BGM::Title);

	static ConstructorHelpers::FClassFinder<UUserWidget> LoginWidget(TEXT("/Game/Widget/Login/WB_LoginMain"));
	if (LoginWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), LoginWidget.Class);
	}
}

void ALoginGameMode::StartPlay()
{
	Super::StartPlay();

	SetMainWidget();
}

void ALoginGameMode::SaveLoginData(FString Email, FString id)
{
	USaveLoginData* pLoginData = NewObject<USaveLoginData>(this, USaveLoginData::StaticClass());
	pLoginData->userEmail = Email;
	pLoginData->userId = id;

	UGameplayStatics::SaveGameToSlot(pLoginData, login_keys::login_data_slot_name, 0);
}

void ALoginGameMode::LoadLoginData(FString& Email, FString& id)
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));
	if (nullptr == loginData)
	{
		loginData = GetMutableDefault<USaveLoginData>();
		SaveLoginData(loginData->userEmail, loginData->userId);
	}

	Email = loginData->userEmail;
	id = loginData->userId;
}