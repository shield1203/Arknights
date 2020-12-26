#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Operator.h"
#include "TowerBlock.generated.h"

UENUM(BlueprintType)
enum class ETowerBlockType : uint8
{
	UpBlock UMETA(DisplayName = "UpBlock"),
	DownBlock UMETA(DisplayName = "DownBlock"),
};

UCLASS()
class ARKNIGHTS_API ATowerBlock : public AActor
{
	GENERATED_BODY()
	
protected:	
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* m_staticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* m_collisionCapsuleComponent;

	UPROPERTY()
	class UOperatorComponent* m_operatorComponent;

	UPROPERTY()
	UOperator* m_operatorData;

	UPROPERTY()
	class UMaterialInterface* m_materialInstance;

	UPROPERTY()
	TMap<class UDecalComponent*, FVector2D> m_attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* m_HPBarComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETowerBlockType m_type;

	float m_ferpPercent = 0.f;

	bool m_turnColor;

	FVector m_InitColor = FVector(0.5f, 0.5f, 0.5f);

	FVector m_ResultColor = FVector(0.130859f, 0.697917f, 0.130859f);

	UPROPERTY()
	int32 m_blockUnit = 0;

	UPROPERTY()
	float m_operatorCurHP = 0;

protected:
	virtual void BeginPlay() override;

public:	
	ATowerBlock();

	virtual void Tick(float DeltaTime) override;

	bool CanPlacement(EOperatorClass operatorClass);

	bool CheckPreparePlacement();

	void AppearPlacementBlock(float DeltaTime);

	void StartPlacement(UOperator* operatorData);

	UFUNCTION(BlueprintCallable)
	float GetCurHP();

	bool IsPlacementOperator();

	bool CanBlock();

	void AddBlockUnit();

	void RemoveBlockUnit();

	UFUNCTION(BlueprintCallable)
	void UnitAttack();

	void OperatorDamaged(float Damage);

	void UnitDie();

	UFUNCTION(BlueprintCallable)
	void UnitWithdraw();
};