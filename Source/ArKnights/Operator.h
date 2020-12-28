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
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Replacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MiniThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WholeBody;
};

USTRUCT(BlueprintType)
struct FOperatorRange : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOperatorCode Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YRange;
};

USTRUCT(BlueprintType)
struct FOperatorExpData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxExp;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UOperator : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	EOperatorCode m_code;

	UPROPERTY()
	int32 m_level;

	UPROPERTY()
	float m_curExp;

	UPROPERTY()
	int32 m_rank;

	UPROPERTY()
	int32 m_potentialAbility;

	UPROPERTY()
	int32 m_reliability;

	UPROPERTY()
	FOperatorData m_data;

	UPROPERTY()
	TArray<FOperatorRange> m_attackRange;

	UPROPERTY()
	class UTexture2D* m_thumbnail;

	UPROPERTY()
	class UTexture2D* m_miniThumbnail;

	UPROPERTY()
	class UTexture2D* m_wholeBody;

public:
	UOperator();
	
	void Initialize(EOperatorCode code, int32 level, float curExp, int32 rank, int32 potentialAbility, int32 reliability);

	void LoadOperatorData(EOperatorCode Operatorcode);

	UFUNCTION(BlueprintCallable)
	EOperatorCode GetOperatorCode() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCode() const;

	UFUNCTION(BlueprintCallable)
	int32 GetLevel() const;

	UFUNCTION(BlueprintCallable)
	float GetExpPercent();

	UFUNCTION(BlueprintCallable)
	int32 GetRank() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPotentialAbility() const ;

	UFUNCTION(BlueprintCallable)
	int32 GetReliability() const;

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	EOperatorRarity GetRarity() const;

	UFUNCTION(BlueprintCallable)
	EOperatorClass GetClass() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCost() const;

	UFUNCTION(BlueprintCallable)
	float GetAtk() const;

	UFUNCTION(BlueprintCallable)
	TArray<FOperatorRange> GetAttackRange() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetThumbnail() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetMiniThumbnail() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetWholeBody() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHP() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBlock() const;
};
