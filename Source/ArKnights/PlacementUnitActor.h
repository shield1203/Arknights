#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Operator.h"
#include "PlacementUnitActor.generated.h"

UCLASS()
class ARKNIGHTS_API APlacementUnitActor : public APaperFlipbookActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

public:
	APlacementUnitActor();

	void Initialize(EOperatorCode operatorCode);

	void SetFlipbookLocation(float x, float y, float z);
};
