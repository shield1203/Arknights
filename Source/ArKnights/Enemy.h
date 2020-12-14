#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Enemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyCode : uint8
{
	Originium_Slug UMETA(DisplayName = "Enemy_Originium Slug"),
	Soldier UMETA(DisplayName = "Enemy_Soldier"),
};

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
};

UCLASS()
class ARKNIGHTS_API UEnemy : public UObject
{
	GENERATED_BODY()
	
private:
	EEnemyCode m_code;

	FString m_name;

	float m_maxHP;

	float m_atk;

	float m_speed;

public:
	UEnemy();

	void Initialize(EEnemyCode code);

	void LoadEnemyData(EEnemyCode code);

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHP() const;

	UFUNCTION(BlueprintCallable)
	float GetAtk() const;

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const;
};
