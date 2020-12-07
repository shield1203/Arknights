#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Operator.h"
#include "OperationSpectator.generated.h"

class APlacementUnitActor;

UCLASS()
class ARKNIGHTS_API AOperationSpectator : public ASpectatorPawn
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	bool m_prepareUnitSetUp = false;

	UPROPERTY()
	bool m_selectedOperatorButton = false;

	UPROPERTY()
	EOperatorCode m_selectedOperatorCode;

	UPROPERTY()
	EOperatorClass m_selectedOperatorClass;

	UPROPERTY()
	APlacementUnitActor* m_placementUnitActor;

	UPROPERTY()
	TArray<EOperatorCode> m_placementOperators;

public:
	AOperationSpectator();

	UFUNCTION(BlueprintCallable)
	bool IsSelectedOperator(EOperatorCode operatorCode) const;

	UFUNCTION(BlueprintCallable)
	void SetSelectOperator(EOperatorCode operatorCode, EOperatorClass operatorClass);

	UFUNCTION(BlueprintCallable)
	EOperatorClass GetSelectedOperatorClass();

	UFUNCTION(BlueprintCallable)
	bool IsSelectedOperatorButton() const;

	UFUNCTION(BlueprintCallable)
	bool IsPrepareUnitSetUp() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlacementOperator(EOperatorCode operatorCode);

	UFUNCTION(BlueprintCallable)
	void StartPrepareUnit(UOperator* operatorData);

	UFUNCTION(BlueprintCallable)
	void SetPrepareUnitLocation(FVector DestLocation, bool onTowerBlock = false);

	UFUNCTION(BlueprintCallable)
	void FinishPrepareUnitSetUp(class ATowerBlock* towerBlock);

	UFUNCTION(BlueprintCallable)
	void AddPlacementOperator(EOperatorCode operatorCode);

	UFUNCTION(BlueprintCallable)
	void RemovePlacementOperator(EOperatorCode operatorCode);
};
