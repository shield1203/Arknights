#include "ArKnightsGameInstance.h"
#include "ArKnights_Keys.h"
#include "SaveLoginData.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "ItemManager.h"
#include "OperatorManager.h"
#include "ShopManager.h"
#include "UserDataManager.h"
#include "WidgetManager.h"
#include "OperationManager.h"
//#include "UObject/ConstructorHelpers.h"

UArKnightsGameInstance::UArKnightsGameInstance()
{
	TArray<FString> DataTablePath;
	DataTablePath.Add(data_table_keys::item);
	DataTablePath.Add(data_table_keys::opertator);
	DataTablePath.Add(data_table_keys::exp);
	DataTablePath.Add(data_table_keys::operation);
	DataTablePath.Add(data_table_keys::operatorExp);
	DataTablePath.Add(data_table_keys::operatorFlipbook);
	DataTablePath.Add(data_table_keys::operatorRange);

	for (FString path : DataTablePath)
	{
		UDataTable* pDataTable = LoadObject<UDataTable>(this, *path);

		if (pDataTable)
		{
			m_gameDataTables.Add(pDataTable);
		}
	}

	m_itemManager = CreateDefaultSubobject<UItemManager>(TEXT("GameInstance_ItemManager"));
	m_operatorManager = CreateDefaultSubobject<UOperatorManager>(TEXT("GameInstance_OperatorManager"));
	m_shopManager = CreateDefaultSubobject<UShopManager>(TEXT("GameInstance_ShopManager"));
	m_userDataManager = CreateDefaultSubobject<UUserDataManager>(TEXT("GameInstance_UserDataManager"));
	m_widgetManager = CreateDefaultSubobject<UWidgetManager>(TEXT("GameInstance_WidgetManager"));
	m_operationManager = CreateDefaultSubobject<UOperationManager>(TEXT("GameInstance_OperationManager"));
}

FString UArKnightsGameInstance::GetMyId() const
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));
	
	return loginData->userId;
}

UDataTable* UArKnightsGameInstance::GetDataTable(EGameDataTable dataTable) const
{
	return m_gameDataTables[static_cast<uint8>(dataTable)];
}

UItemManager* UArKnightsGameInstance::GetItemManager() const
{
	return m_itemManager;
}

UOperatorManager* UArKnightsGameInstance::GetOperatorManager() const
{
	return m_operatorManager;
}

UShopManager* UArKnightsGameInstance::GetShopManager() const
{
	return m_shopManager;
}

UUserDataManager* UArKnightsGameInstance::GetUserDataManager() const
{
	return m_userDataManager;
}

UWidgetManager* UArKnightsGameInstance::GetWidgetManager() const
{
	return m_widgetManager;
}

UOperationManager* UArKnightsGameInstance::GetOperationManager() const
{
	return m_operationManager;
}