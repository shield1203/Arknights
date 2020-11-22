#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "OperationManager.generated.h"

USTRUCT(BlueprintType)
struct FOperationData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Episode;

	UPROPERTY()
	int32 Chapter;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Sanity; // �Һ��̼�

	UPROPERTY()
	int32 Level; //  ��õ ��� ����

	UPROPERTY()
	int32 Enemies; // �� ���� �����ּ�

	UPROPERTY()
	int32 UnitLimit; // �ʵ忡 ��ġ������ ���ּ�

	UPROPERTY()
	int32 LifePoint; // ������ī����

	UPROPERTY()
	int32 EXP; // Ŭ���� ����ġ

	UPROPERTY()
	int32 LMD; // Ŭ���� ���� LMD

	UPROPERTY()
	FString Explanation;
};

USTRUCT(BlueprintType)
struct FClearOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 episode;

	UPROPERTY()
	int32 chapter;

	UPROPERTY()
	int32 clear_rank;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UOperationManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UHttpSystem* m_httpSystem;

	UPROPERTY()
	int32 m_curEpisode;

	UPROPERTY()
	int32 m_curChapter;

	UPROPERTY()
	TArray<FClearOperation>m_clearOperation;

public:
	UOperationManager();

	UFUNCTION(BlueprintCallable)
	void RequestClearOperations();

	UFUNCTION(BlueprintCallable)
	void OnClearOperationsResponsRecived(bool IsSuccess, FString respons);

	UFUNCTION(BlueprintCallable)
	void SetClearOperation(FString clearOperations);

	UFUNCTION(BlueprintCallable)
	void SetEpisode(int32 selectedEpisode);

	UFUNCTION(BlueprintCallable)
	void SetChapter(int32 selectedChapter);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxEpisode();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxChapter(int32 episode);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetPlayableEpisode();

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetPlayableChapter(int32 episode);

	UFUNCTION(BlueprintCallable)
	int32 GetCurEpisode() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurChapter() const;

	UFUNCTION(BlueprintCallable)
	int32 GetOperationClearRank(int32 episode, int32 chapter) const;

	UFUNCTION(BlueprintCallable)
	FString GetOperationName(int32 episode, int32 chapter) const;

	UFUNCTION(BlueprintCallable)
	int32 GetOperationLevel(int32 episode, int32 chapter) const;

	UFUNCTION(BlueprintCallable)
	int32 GetOperationSanity(int32 episode, int32 chapter) const;

	UFUNCTION(BlueprintCallable)
	FString GetOperationExplanation(int32 episode, int32 chapter) const;
};
