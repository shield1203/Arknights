#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawnPlace.generated.h"

UCLASS()
class ARKNIGHTS_API AEnemySpawnPlace : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* m_staticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_placeNum;

protected:
	virtual void BeginPlay() override;

public:	
	AEnemySpawnPlace();

	virtual void Tick(float DeltaTime) override;

	int32 GetPlaceNum();

	void SpawnEnemy(EEnemyCode enemyCode, TArray<float>DestinationXPos, TArray<float>DestinationYPos, TArray<float>HoldingTime);
};
