#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Operator.generated.h"

UENUM(BlueprintType)
enum class EOperatorCode : uint8
{
	Amiya UMETA(DisplayName = "Operator_Amiya"),
	Croissant UMETA(DisplayName = "Operator_Croissant"),
	Fang UMETA(DisplayName = "Operator_Fang"),
	Hibiscus UMETA(DisplayName = "Operator_Hibiscus"),
	Hoshiguma UMETA(DisplayName = "Operator_Hoshiguma"),
	Kroos UMETA(DisplayName = "Operator_Kroos"),
	Lancet UMETA(DisplayName = "Operator_Lancet"),
	Meteorite UMETA(DisplayName = "Operator_Meteorite"),
	Noir_Corne UMETA(DisplayName = "Operator_Noir Corne"),
};

UENUM(BlueprintType)
enum class EOperatorRarity : uint8
{
	Star_1 UMETA(DisplayName = "Star_1"),
	Star_2 UMETA(DisplayName = "Star_2"),
	Star_3 UMETA(DisplayName = "Star_3"),
	Star_4 UMETA(DisplayName = "Star_4"),
	Star_5 UMETA(DisplayName = "Star_5"),
	Star_6 UMETA(DisplayName = "Star_6"),
};

UENUM(BlueprintType)
enum class EOperatorClass : uint8
{
	Vanguard UMETA(DisplayName = "Vanguard"),
	Guard UMETA(DisplayName = "Guard"),
	Defender UMETA(DisplayName = "Defender"),
	Specialist UMETA(DisplayName = "Specialist"),
	Sniper UMETA(DisplayName = "Sniper"),
	Caster UMETA(DisplayName = "Caster"),
	Medic UMETA(DisplayName = "Medic"),
	Supporter UMETA(DisplayName = "Supporter"),
};

UENUM(BlueprintType)
enum class EFaction : uint8
{
	Abyssal UMETA(DisplayName = "Abyssal"),
	Babel UMETA(DisplayName = "Babel"),
	BlackSteel UMETA(DisplayName = "BlackSteel"),
	Kazimierz UMETA(DisplayName = "Kazimierz"),
	Kjerag UMETA(DisplayName = "Kjerag"),
	Laterano UMETA(DisplayName = "Laterano"),
	Leithania UMETA(DisplayName = "Leithania"),
	Lungmen UMETA(DisplayName = "Lungmen"),
	Penguin_Logistics UMETA(DisplayName = "Penguin Logistics"),
	Rhine_Lab UMETA(DisplayName = "Rhine Lab"),
	Rhodes_Island UMETA(DisplayName = "Rhodes Island"),
};

USTRUCT(BlueprintType)
struct FOperatorData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOperatorRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOperatorClass Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFaction Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 RES;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 RDP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 DP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ASPD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Thumbnail;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UOperator : public UObject
{
	GENERATED_BODY()
	
protected:
	EOperatorCode m_code;

	uint8 m_level;

	FOperatorData m_data;

	class UTexture2D* m_thumbnail;

public:
	UOperator();
	
	void Initialize(EOperatorCode code, uint8 level);

	void LoadOperatorData(EOperatorCode Operatorcode);

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetThumbnail() const;

	UFUNCTION(BlueprintCallable)
	EOperatorRarity GetRarity() const;

	UFUNCTION(BlueprintCallable)
	EOperatorClass GetClass() const;
};
