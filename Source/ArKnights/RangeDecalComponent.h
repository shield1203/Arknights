#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "RangeDecalComponent.generated.h"

UCLASS()
class ARKNIGHTS_API URangeDecalComponent : public UDecalComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UBoxComponent* m_collisionBoxComponent;

public:
	URangeDecalComponent();

	class UBoxComponent* GetCollisionBoxComponent() const;

	void SetComponentTransform(int32 xPos, int32 yPos);

	class AEnemyUnit* CheckCollision();
};
