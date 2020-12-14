#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enemy.h"
#include "Engine/DataTable.h"
#include "EnemyManager.generated.h"

USTRUCT(BlueprintType)
struct FOperationEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyCode EnemyCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpawnPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> DestinationXPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> DestinationYPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> HoldingTime;
};

UCLASS()
class ARKNIGHTS_API UEnemyManager : public UObject
{
	GENERATED_BODY()
	
private:
	float m_second = 0;

	int32 m_spawnIndex = 0;

	TArray<FOperationEnemyData>m_operationEnemyData;

public:
	UEnemyManager();

	void LoadOperationEnemyData(int32 Episode, int32 Chapter);

	TArray<EEnemyCode> GetOperationEnemy(int32 Episode, int32 Chapter);

	void OperationStart();

	void CheckEnemySpawnTime(float deltaTime);
};
