#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Operator.h"
#include "OperatorManager.generated.h"

USTRUCT()
struct FOperatorInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint8 operator_num;

	UPROPERTY()
	uint8 owner_id;

	UPROPERTY()
	EOperatorCode operator_code;

	UPROPERTY()
	uint8 level;

	UPROPERTY()
	uint8 cur_exp;
	
	UPROPERTY()
	uint8 rank;

	UPROPERTY()
	uint8 potential_ability;

	UPROPERTY()
	uint8 reliability;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UOperatorManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TMap<EOperatorCode, UOperator*> m_operators;

public:
	UOperatorManager();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetOperators(FString operators);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TMap<EOperatorCode, UOperator*> GetOperators();
};
