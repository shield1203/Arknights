#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "ShopManager.generated.h"

UENUM(BlueprintType)
enum class EShopMenu : uint8
{
	Recommendation UMETA(DisplayName = "Menu_Recommendation"),
	Orundum UMETA(DisplayName = "Menu_Orundum"),
	Package UMETA(DisplayName = "Menu_Package"),
	Collection UMETA(DisplayName = "Menu_Collection"),
	Certificate UMETA(DisplayName = "Menu_Certificate"),
	Furniture UMETA(DisplayName = "Menu_Furniture"),
	Credit UMETA(DisplayName = "Menu_Credit"),
};

USTRUCT(Atomic, BlueprintType, Blueprintable)
struct FOriginite_Prime_Goods
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool sold_out;
};

USTRUCT(Atomic, BlueprintType, Blueprintable)
struct FCredit_Goods
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemCode itemCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool sold_out;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UShopManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<FOriginite_Prime_Goods> m_originitePrimeGoods;

	UPROPERTY()
	TArray<UItem*> m_creditGoods;

public:
	UShopManager();

	UFUNCTION(BlueprintCallable, Category = "ShopManager")
	FString GetMenuKey(EShopMenu shopMenu);

	UFUNCTION(BlueprintCallable, Category = "ShopManager")
	void SetOriginite_Prime_Goods(FString originite_Priem_Goods);

	UFUNCTION(BlueprintCallable, Category = "ShopManager")
	void SetCredit_Goods(FString credit_Goods);

	UFUNCTION(BlueprintCallable, Category = "ShopManager")
	TArray<FOriginite_Prime_Goods> GetOriginitePrimeGoods();

	UFUNCTION(BlueprintCallable, Category = "ShopManager")
	TArray<UItem*> GetCreditGoods();
};