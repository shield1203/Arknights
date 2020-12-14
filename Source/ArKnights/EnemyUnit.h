#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemyUnit.generated.h"

UCLASS()
class ARKNIGHTS_API AEnemyUnit : public AActor
{
	GENERATED_BODY()
	
protected:	
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEnemyComponent* m_enemyComponent;

	UEnemy* m_enemyData;

	FTimerHandle m_holdingTimerHandle;

	int32 m_destinationIndex = 0;

	TArray<float>m_destinationXPos;

	TArray<float>m_destinationYPos;

	TArray<float>m_holdingTime;

	bool m_holding = false;

protected:
	virtual void BeginPlay() override;

public:	
	AEnemyUnit();

	void Initialize(EEnemyCode enemyCode, TArray<float>DestinationXPos, TArray<float>DestinationYPos, TArray<float>HoldingTime);

	virtual void Tick(float DeltaTime) override;

	void MoveToLocation();

	void CheckDestination();

	void CancelToHolding();
};
