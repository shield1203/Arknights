#include "OperationManager.h"
#include "ArKnightsGameInstance.h"
#include "HttpSystem.h"
#include "ArKnights_Keys.h"
#include "Kismet/GameplayStatics.h"
#include "JsonObjectConverter.h"
#include "SaveLoginData.h"

UOperationManager::UOperationManager()
{
	m_httpSystem = CreateDefaultSubobject<UHttpSystem>(TEXT("OperationManager_HttpSystem"));
	m_httpSystem->OnOperationResponsReceiveCallback.AddDynamic(this, &UOperationManager::OnClearOperationsResponsRecived);
}

void UOperationManager::RequestClearOperations()
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));

	m_httpSystem->RequestOperation(loginData->userId);
}

void UOperationManager::OnClearOperationsResponsRecived(bool IsSuccess, FString respons)
{
	if (IsSuccess)
	{
		SetClearOperation(respons);
	}
}

void UOperationManager::SetClearOperation(FString clearOperations)
{
	m_clearOperation.Reset();
	
	if (!FJsonObjectConverter::JsonArrayStringToUStruct(clearOperations, &m_clearOperation, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}
}

void UOperationManager::SetEpisode(int32 selectedEpisode)
{
	m_curEpisode = selectedEpisode;
}

void UOperationManager::SetChapter(int32 selectedChapter)
{
	m_curChapter = selectedChapter;
}

int32 UOperationManager::GetMaxEpisode()
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	int32 maxEpisode = 0;
	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (maxEpisode < pOperationData->Episode)
		{
			maxEpisode = pOperationData->Episode;
		}
	}

	return maxEpisode;
}

int32 UOperationManager::GetMaxChapter(int32 episode)
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	int32 maxChapter = 0;
	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (episode == pOperationData->Episode && maxChapter < pOperationData->Chapter)
		{
			maxChapter = pOperationData->Chapter;
		}
	}

	return maxChapter;
}

TArray<int32> UOperationManager::GetPlayableEpisode()
{
	TArray<int32>playableEpisode;
	playableEpisode.Add(0);

	int32 maxClearEpisode = 0;
	int32 maxClearChapter = 0;
	for (auto clearOperation : m_clearOperation)
	{
		if (maxClearEpisode < clearOperation.episode)
		{
			playableEpisode.Add(clearOperation.episode);
			maxClearEpisode = maxClearEpisode;
			maxClearChapter = 0;
		}

		if (maxClearEpisode == clearOperation.episode && maxClearChapter < clearOperation.chapter)
		{
			maxClearChapter = clearOperation.chapter;
		}
	}

	if (maxClearEpisode < GetMaxEpisode())
	{
		if (maxClearChapter == GetMaxChapter(maxClearEpisode))
		{
			playableEpisode.Add(++maxClearEpisode);
		}
		else
		{
			playableEpisode.Add(-1); // 이전 에피소드를 클리어해 주세요 이미지
		}
	}

	return playableEpisode;
}

TArray<int32> UOperationManager::GetPlayableChapter(int32 episode)
{
	TArray<int32>playableChapter;

	int32 maxClearChapter = 0;
	for (auto clearOperation : m_clearOperation)
	{
		if (clearOperation.episode == episode && maxClearChapter < clearOperation.chapter)
		{
			maxClearChapter = clearOperation.chapter;
			playableChapter.Add(clearOperation.chapter);
		}
	}

	if (maxClearChapter < GetMaxChapter(episode))
	{
		playableChapter.Add(++maxClearChapter);
	}

	return playableChapter;
}

int32 UOperationManager::GetCurEpisode() const
{
	return m_curEpisode;
}

int32 UOperationManager::GetCurChapter() const
{
	return m_curChapter;
}

int32 UOperationManager::GetOperationClearRank(int32 episode, int32 chapter) const
{
	for (auto clearOperation : m_clearOperation)
	{
		if (episode == clearOperation.episode && chapter == clearOperation.chapter)
		{
			return clearOperation.clear_rank;
		}
	}

	return 0;
}

FString UOperationManager::GetOperationName() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->Name;
		}
	}

	return TEXT("Unknown");
}

int32 UOperationManager::GetOperationLevel() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->Level;
		}
	}

	return 0;
}

int32 UOperationManager::GetOperationSanity() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->Sanity;
		}
	}

	return 0;
}

int32 UOperationManager::GetOperationEnemies() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->Enemies;
		}
	}

	return 0;
}

int32 UOperationManager::GetOperationUnitLimit() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->UnitLimit;
		}
	}

	return 0;
}

int32 UOperationManager::GetOperationLifePoint() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->LifePoint;
		}
	}

	return 0;
}

FString UOperationManager::GetOperationExplanation() const
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperationData)->GetRowNames().Num(); i++)
	{
		FOperationData* pOperationData = pGameInstance->GetDataTable(EGameDataTable::OperationData)->FindRow<FOperationData>(FName(*(FString::FormatAsNumber(static_cast<int32>(i)))), FString(""));
		if (m_curEpisode == pOperationData->Episode && m_curChapter == pOperationData->Chapter)
		{
			return pOperationData->Explanation;
		}
	}

	return TEXT("Unknown");
}