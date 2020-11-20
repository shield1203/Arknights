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
	int32 sanity; // �Һ��̼�

	UPROPERTY()
	int32 level; //  ��õ ��� ����

	UPROPERTY()
	int32 enemies; // �� ���� �����ּ�

	UPROPERTY()
	int32 unitLimit; // �ʵ忡 ��ġ������ ���ּ�

	UPROPERTY()
	int32 lifePoint; // ������ī����

	UPROPERTY()
	int32 EXP; // Ŭ���� ����ġ

	UPROPERTY()
	int32 LMD; // Ŭ���� ���� LMD

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
