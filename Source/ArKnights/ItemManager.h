#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "ItemManager.generated.h"

USTRUCT()
struct FItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint8 item_num;

	UPROPERTY()
	uint8 owner_id;

	UPROPERTY()
	EItemCode item_code;

	UPROPERTY()
	int32 amount;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UItemManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UHttpSystem* m_httpSystem;

	UPROPERTY()
	TMap<EItemCode, UItem*> m_items;

	UPROPERTY()
	TMap<EItemCode, UItem*> m_groupItems;

public:
	UItemManager();

	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void RequestItems();

	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void OnItemResponsReceived(bool IsSuccess, FString respons);

	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void SetItems(FString items);

	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	int32 GetItemAmount(EItemCode itemCode);

	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	TMap<EItemCode, UItem*> GetGroupItem(EItemType type);
};