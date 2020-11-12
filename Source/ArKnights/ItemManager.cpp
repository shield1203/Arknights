#include "ItemManager.h"
#include "ArKnightsGameInstance.h"
#include "ArKnights_Keys.h"
#include "SaveLoginData.h"
#include "Kismet/GameplayStatics.h"
#include "HttpSystem.h"
#include "JsonObjectConverter.h"

UItemManager::UItemManager()
{
	m_httpSystem = CreateDefaultSubobject<UHttpSystem>(TEXT("ItemManager_HttpSystem"));
	m_httpSystem->OnItemResponsReceiveCallback.AddDynamic(this, &UItemManager::OnItemResponsReceived);
}

void UItemManager::RequestItems()
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));

	m_httpSystem->RequestItems(loginData->userId);
}

void UItemManager::OnItemResponsReceived(bool IsSuccess, FString respons)
{
	if (IsSuccess)
	{
		SetItems(respons);
	}
}

void UItemManager::SetItems(FString items)
{
	m_items.Reset();

	if (items == "") 
	{
		UE_LOG(LogTemp, Warning, TEXT("item noting"));
		return;
	}
 
	TArray<FItemInfo> itemInfo;
	if (!FJsonObjectConverter::JsonArrayStringToUStruct(items, &itemInfo, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}
	
	for (auto item : itemInfo)
	{
		UItem* pAddItem = NewObject<UItem>(this, UItem::StaticClass());
		pAddItem->Initialize(item.item_code, item.amount);
		m_items.Add(item.item_code, pAddItem);
	}
}

int32 UItemManager::GetItemAmount(EItemCode itemCode)
{
	if (m_items.Contains(itemCode))
	{
		return m_items[itemCode]->GetAmount();
	}

	return 0;
}

TMap<EItemCode, UItem*> UItemManager::GetGroupItem(EItemType type)
{
	m_groupItems.Reset();

	if (type == EItemType::All)
	{
		for (auto& item : m_items)
		{
			if (item.Key != EItemCode::Originite_Prime && item.Key != EItemCode::Credit)
			{
				m_groupItems.Add(item);
			}
		}
	}
	else
	{
		for (auto& item : m_items)
		{
			if (item.Value->GetType() == type && item.Key != EItemCode::Originite_Prime && item.Key != EItemCode::Credit)
			{
				m_groupItems.Add(item);
			}
		}
	}

	return m_groupItems;
}