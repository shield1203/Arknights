#include "UserDataManager.h"
#include "ArKnightsGameInstance.h"
#include "ArKnights_Keys.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "SaveLoginData.h"
#include "HttpSystem.h"

UUserDataManager::UUserDataManager()
{
	m_httpSystem = CreateDefaultSubobject<UHttpSystem>(TEXT("UserDataManager_HttpSystem"));
	m_httpSystem->OnLoginResponsReceivedCallback.AddDynamic(this, &UUserDataManager::OnRequestUserDataReceived);
}

void UUserDataManager::RequestUserData()
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));

	m_httpSystem->RequestLogin(loginData->userId);
}

void UUserDataManager::OnRequestUserDataReceived(bool IsSuccess, FString respons)
{
	if (IsSuccess)
	{
		SetUserData(respons);
	}
}

void UUserDataManager::SetUserData(FString userDataJson)
{
	if (userDataJson == "") return;

	TArray<FUserData> userData;
	if (!FJsonObjectConverter::JsonArrayStringToUStruct(userDataJson, &userData, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}

	for (auto myData : userData)
	{
		m_userData.user_id = myData.user_id;
		m_userData.user_name = myData.user_name;
		m_userData.level = myData.level;
		m_userData.cur_exp = myData.cur_exp;
	}
}

void UUserDataManager::SetExpData(int32 level)
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	FExpData* pExpData = pGameInstance->GetDataTable(EGameDataTable::ExpData)->FindRow<FExpData>(FName(*(FString::FormatAsNumber(level))), FString(""));

	m_expData.MaxAp = pExpData->MaxAp;
	m_expData.MaxExp = pExpData->MaxExp;
}

FString UUserDataManager::GetUserName() const
{
	return m_userData.user_name;
}

int32 UUserDataManager::GetUserLevel() const
{
	return m_userData.level;
}

float UUserDataManager::GetCurExp()
{
	return m_userData.cur_exp;
}

float UUserDataManager::GetMaxExp()
{
	SetExpData(m_userData.level);

	return m_expData.MaxExp;
}

float UUserDataManager::GetExpPercent()
{
	SetExpData(m_userData.level);

	return m_userData.cur_exp / m_expData.MaxExp;
}

int32 UUserDataManager::GetCurAp() const
{
	return m_expData.MaxAp;
}

int32 UUserDataManager::GetMaxAp() const
{
	return m_expData.MaxAp;
}