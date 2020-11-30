#pragma once

#include "CoreMinimal.h"
#include "ArKnightsGameModeBase.h"
#include "Operator.h"
#include "OperationGameMode.generated.h"

class UOperationManager;

UCLASS()
class ARKNIGHTS_API AOperationGameMode : public AArKnightsGameModeBase
{
	GENERATED_BODY()
	
private:
	UOperationManager* m_operationManager;

	FTimerHandle m_costTimerHandle;

	UPROPERTY()
	int32 m_dieEnemyCount = 0;

	UPROPERTY()
	int32 m_curCost = 0;

	UPROPERTY()
	float m_costGauge = 0;

	UPROPERTY()
	bool m_selected = false;

	UPROPERTY()
	EOperatorCode m_selectedOperator;

	UPROPERTY()
	TArray<EOperatorCode> m_placementUnits; // ¹èÄ¡µÈ À¯´Ö

protected:
	virtual void StartPlay();

public:
	AOperationGameMode();

	UFUNCTION(BlueprintCallable)
	int32 GetCurCost() const;

	UFUNCTION(BlueprintCallable)
	float GetCostGauge() const;

	UFUNCTION(BlueprintCallable)
	void AddCost(int32 value);

	UFUNCTION(BlueprintCallable)
	void AddCostGauge();

	UFUNCTION(BlueprintCallable)
	void AddDieEnemyCount();
};
