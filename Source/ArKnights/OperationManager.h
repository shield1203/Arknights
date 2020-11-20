#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OperationManager.generated.h"

USTRUCT(BlueprintType)
struct FOperationData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint8 episode;

	UPROPERTY()
	uint8 chapter;

	UPROPERTY()
	int32 sanity; // 소비이성

	UPROPERTY()
	int32 level; //  추천 평균 레벨

	UPROPERTY()
	int32 enemies; // 총 등장 적유닛수

	UPROPERTY()
	int32 unitLimit; // 필드에 배치가능한 유닛수

	UPROPERTY()
	int32 lifePoint; // 라이프카운터

	UPROPERTY()
	int32 EXP; // 클리어 경험치

	UPROPERTY()
	int32 LMD; // 클리어 보상 LMD

	UPROPERTY()
	FString explanation;
};

USTRUCT(BlueprintType)
struct FClearOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint8 episode;

	UPROPERTY()
	uint8 chapter;

	UPROPERTY()
	uint8 clear_rank;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UOperationManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	uint8 m_curEpisode;

	UPROPERTY()
	uint8 m_curChapter;

	UPROPERTY()
	TArray<FClearOperation>m_clearOperation;

public:
	UOperationManager();

	UFUNCTION(BlueprintCallable)
	void SetEpisode(uint8 selectedEpisode);

	UFUNCTION(BlueprintCallable)
	void SetChapter(uint8 selectedChapter);

	UFUNCTION(BlueprintCallable)
	uint8 GetCurEpisode() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetCurChapter() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetOperationClearRank(uint8 episode, uint8 chapter) const;
};
