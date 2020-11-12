#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemCode : uint8
{
	Orundum UMETA(DisplayName = "Item_Orundum"),
	LMD UMETA(DisplayName = "Item_LMD"),
	Pure_Gold UMETA(DisplayName = "Item_Pure Gold"),
	Recruitment_Permit UMETA(DisplayName = "Item_Recruitment Permit"),
	Funiture_Part UMETA(DisplayName = "Item_Funiture Part"),
	Strategic_Battle_Record UMETA(DisplayName = "Item_Strategic Battle Record"),
	Tactical_Battle_Record UMETA(DisplayName = "Item_Tactical Battle Record"),
	Frontline_Battle_Record UMETA(DisplayName = "Item_Frontline Battle Record"),
	Drill_Battle_Record UMETA(DisplayName = "Item_Drill Battle Record"),
	Chip_Catalyst UMETA(DisplayName = "Item_Chip Catalyst"),
	Vanguard_Chip UMETA(DisplayName = "Item_Vanguard Chip"),
	Guard_Chip UMETA(DisplayName = "Item_Guard Chip"),
	Defender_Chip UMETA(DisplayName = "Item_Defender Chip"),
	Sniper_Chip UMETA(DisplayName = "Item_Sniper Chip"),
	Caster_Chip UMETA(DisplayName = "Item_Caster Chip"),
	Medic_Chip UMETA(DisplayName = "Item_Medic Chip"),
	Supporter_Chip UMETA(DisplayName = "Item_Supporter Chip"),
	Specialist_Chip UMETA(DisplayName = "Item_Specialist Chip"),
	Originite_Prime UMETA(DisplayName = "Item_Originite Prime"),
	Credit UMETA(DisplayName = "Item_Credit"),
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	Gold UMETA(DisplayName = "Grade_Gold"),
	Pink UMETA(DisplayName = "Grade_Pink"),
	Blue UMETA(DisplayName = "Grade_Blue"),
	Yellow UMETA(DisplayName = "Grade_Yellow"),
	Gray UMETA(DisplayName = "Grade_Gray"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Consume UMETA(DisplayName = "Type_Consume"),
	Foundation UMETA(DisplayName = "Type_Foundation"),
	Promote UMETA(DisplayName = "Type_Promote"),
	All UMETA(DisplayName = "All_Item"),
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemGrade Grade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description2;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UItem : public UObject
{
	GENERATED_BODY()
	
private:
	EItemCode m_code;

	int32 m_amount;

	int32 m_price;

	bool m_soldOut;

	FItemData m_data;

	class UTexture2D* m_image;

	class UTexture2D* m_grade;
public:
	UItem();

	UFUNCTION(BlueprintCallable)
	void Initialize(EItemCode code, int32 amount, int32 price = 0, bool soldOut = false);

	void LoadItemData(EItemCode itemCode);

	UFUNCTION(BlueprintCallable)
	int32 GetAmount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPrice() const;

	UFUNCTION(BlueprintCallable)
	bool IsSoldOut() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetImage() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetGrade() const;

	UFUNCTION(BlueprintCallable)
	EItemType GetType() const;

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	FString GetDescription1() const;

	UFUNCTION(BlueprintCallable)
	FString GetDescription2() const;
};
