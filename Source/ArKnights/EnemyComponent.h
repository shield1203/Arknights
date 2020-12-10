#pragma once

#include "CoreMinimal.h"
#include "UnitComponent.h"
#include "EnemyComponent.generated.h"

UCLASS()
class ARKNIGHTS_API UEnemyComponent : public UUnitComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TArray<UPaperFlipbook*> m_flipbooks;

public:
	void Init();

};
