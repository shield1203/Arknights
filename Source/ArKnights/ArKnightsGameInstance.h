#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArKnightsGameInstance.generated.h"

class UItemManager;
class UOperatorManager;
class UShopManager;
class UUserDataManager;

UENUM(BlueprintType)
enum class EGameDataTable : uint8
{
	ItemData UMETA(DisplayName = "DT_ItemData"),
	OperatorData UMETA(DisplayName = "DT_OperatorData"),
	ExpData UMETA(DisplayName = "DT_ExpData"),
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
};
