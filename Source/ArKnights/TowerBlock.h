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

	UPROPERTY()
	class UOperatorComponent* m_operatorComponent;

	UPROPERTY()
	class UWidgetComponent* m_HPBarComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETowerBlockType m_type;

	float m_ferpPercent = 0.f;

	bool m_turnColor;

	FVector m_InitColor = FVector(0.5f, 0.5f, 0.5f);

	FVector m_ResultColor = FVector(0.130859f, 0.697917f, 0.130859f);

	UOperator* m_operatorData;

protected:
	virtual void BeginPlay() override;

public:	
	ATowerBlock();

	virtual void Tick(float DeltaTime) override;

	bool CanPlacement(EOperatorClass operatorClass);

	bool CheckPreparePlacement();

	void AppearPlacementBlock(float DeltaTime);

	void StartPlacement(UOperator* operatorData);
};