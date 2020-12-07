#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "PlacementUnitActor.generated.h"

class UOperator;

UCLASS()
class ARKNIGHTS_API APlacementUnitActor : public APaperFlipbookActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY()
	TMap<class UDecalComponent*, FVector2D> m_decalComponents;

	UPROPERTY()
	class UMaterialInterface* m_materialInstance;

	UPROPERTY()
	UOperator* m_operatorData;

	float m_x;
	float m_y;
	float m_z;

public:
	APlacementUnitActor();

	void Initialize(UOperator* operatorData);

	void SetFlipbookLocation(float x, float y, float z);

	void SetUnitLocation(FVector DestLocation, bool onTowerBlock = false);

	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	UOperator* GetOperatorData();
};
