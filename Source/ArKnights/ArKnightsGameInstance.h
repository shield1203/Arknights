#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArKnightsGameInstance.generated.h"

class UItemManager;
class UOperatorManager;
class UShopManager;
class UUserDataManager;
class UWidgetManager;
class UOperationManager;
class UEnemyManager;

UENUM(BlueprintType)
enum class EGameDataTable : uint8
{
	ItemData UMETA(DisplayName = "DT_ItemData"),
	OperatorData UMETA(DisplayName = "DT_OperatorData"),
	ExpData UMETA(DisplayName = "DT_ExpData"),
	OperationData UMETA(DisplayName = "DT_OperationData"),
	OperatorExpData UMETA(DisplayName = "DT_OperatorExpData"),
	OperatorFlipbookData UMETA(DisplayName = "DT_OperatorFlipbookData"),
	OperatorRangeData UMETA(DisplayName = "DT_OperatorRangeData"),
	EnemyData UMETA(DisplayName = "DT_EnemyData"),
	EnemyFlipbookData UMETA(DisplayName = "DT_EnemyFlipbookData"),
};

UCLASS(BlueprintType)
class ARKNIGHTS_API UArKnightsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "GameDataTables")
	TArray<class UDataTable*> m_gameDataTables;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UItemManager* m_itemManager;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UOperatorManager* m_operatorManager;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UShopManager* m_shopManager;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UUserDataManager* m_userDataManager;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UWidgetManager* m_widgetManager;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UOperationManager* m_operationManager;

	UPROPERTY(EditAnywhere, Category = "Manager")
	UEnemyManager* m_enemyManager;

public:
	UArKnightsGameInstance();

	UFUNCTION(BlueprintCallable)
	FString GetMyId() const;

	UFUNCTION(BlueprintCallable)
	class UDataTable* GetDataTable(EGameDataTable dataTable) const;

	UFUNCTION(BlueprintCallable)
	UItemManager* GetItemManager() const;

	UFUNCTION(BlueprintCallable)
	UOperatorManager* GetOperatorManager() const;

	UFUNCTION(BlueprintCallable)
	UShopManager* GetShopManager() const;

	UFUNCTION(BlueprintCallable)
	UUserDataManager* GetUserDataManager() const;

	UFUNCTION(BlueprintCallable)
	UWidgetManager* GetWidgetManager() const;

	UFUNCTION(BlueprintCallable)
	UOperationManager* GetOperationManager() const;

	UFUNCTION(BlueprintCallable)
	UEnemyManager* GetEnemyManager() const;
};
