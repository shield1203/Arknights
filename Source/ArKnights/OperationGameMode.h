#pragma once

#include "CoreMinimal.h"
#include "ArKnightsGameModeBase.h"
#include "Operator.h"
#include "OperationGameMode.generated.h"

class UArKnightsGameInstance;
class UEnemyManager;
class UOperationManager;
class UOperatorManager;

UCLASS()
class ARKNIGHTS_API AOperationGameMode : public AArKnightsGameModeBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UArKnightsGameInstance* m_gameInstance;

	// Managers
	UPROPERTY()
	UEnemyManager* m_enemyManager;

	UPROPERTY()
	UOperationManager* m_operationManager;

	UPROPERTY()
	UOperatorManager* m_operatorManager;

	// SubWidgets
	UPROPERTY()
	class UUserWidget* m_missionCompleteWidget;

	UPROPERTY()
	class UUserWidget* m_missionFailedWidget;

	// Timer
	FTimerHandle m_costTimerHandle;

	FTimerHandle m_enemySpawnTimerHandle;

	// Else
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

	UPROPERTY()
	int32 m_lifePoint;

	UPROPERTY()
	int32 m_removeEnemyCount = 0;

protected:
	virtual void StartPlay();

public:
	AOperationGameMode();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PreLoadFlipbookData();

	UFUNCTION(BlueprintCallable)
	int32 GetCurCost() const;

	UFUNCTION(BlueprintCallable)
	float GetCostGauge() const;

	UFUNCTION(BlueprintCallable)
	int32 GetLifePoint() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRemoveEnemy() const;

	UFUNCTION(BlueprintCallable)
	void MinusLifePoint();

	UFUNCTION(BlueprintCallable)
	void AddCost(int32 value);

	UFUNCTION(BlueprintCallable)
	void AddCostGauge();

	UFUNCTION(BlueprintCallable)
	void AddRemoveEnemyCount();

	UFUNCTION(BlueprintCallable)
	void CheckOperationComplete();

	UFUNCTION(BlueprintCallable)
	void CheckEnemySpawn();
};
