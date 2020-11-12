#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "TipManager.generated.h"

USTRUCT(BlueprintType)
struct FTipData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Background;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Tip;
};

UCLASS(BlueprintType)
class ARKNIGHTS_API UTipManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Tip_DataTable")
	class UDataTable* m_tipDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Tip_Image")
	TArray<class UTexture2D*> m_backgrounds;

	int32 m_tipNumber;

	int32 m_maxTipNumber;

public:
	UTipManager();

	UFUNCTION(BlueprintCallable)
	void ChangeTipNumber();

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetBackground() const;

	UFUNCTION(BlueprintCallable)
	FString GetName() const;

	UFUNCTION(BlueprintCallable)
	FString GetTip() const;
};
