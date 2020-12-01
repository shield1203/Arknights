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
	EOperatorCode m_selectedOperator;

	UPROPERTY()
	APlacementUnitActor* m_placementUnit;

	UPROPERTY()
	TArray<EOperatorCode> m_setUpOperators;

public:
	AOperationSpectator();

	UFUNCTION(BlueprintCallable)
	bool IsSelectedOperator(EOperatorCode operatorCode) const;

	UFUNCTION(BlueprintCallable)
	void SetSelectOperator(EOperatorCode operatorCode);

	UFUNCTION(BlueprintCallable)
	bool IsPrepareUnitSetUp() const;

	UFUNCTION(BlueprintCallable)
	void StartPrepareUnit(UOperator* operatorData);

	UFUNCTION(BlueprintCallable)
	void SetPrepareUnitLocation(const FVector DestLocation);

	UFUNCTION(BlueprintCallable)
	void FinishPrepareUnitSetUp();
};
