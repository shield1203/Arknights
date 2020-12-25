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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoxLocationX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoxWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BoxHeight;
};

UCLASS()
class ARKNIGHTS_API UEnemy : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	EEnemyCode m_code;

	UPROPERTY()
	FString m_name;

	UPROPERTY()
	float m_maxHP;

	UPROPERTY()
	float m_atk;

	UPROPERTY()
	float m_speed;

	UPROPERTY()
	float m_boxLocationX;

	UPROPERTY()
	float m_boxWidth;

	UPROPERTY()
	float m_boxHeight;

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

	UFUNCTION(BlueprintCallable)
	float GetBoxLocationX() const;

	UFUNCTION(BlueprintCallable)
	float GetBoxWidth() const;

	UFUNCTION(BlueprintCallable)
	float GetBoxHeight() const;
};
