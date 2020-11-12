#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "UserDataManager.generated.h"

class UHttpSystem;

USTRUCT()
struct FUserData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 user_id;

	UPROPERTY()
	FString user_email;

	UPROPERTY()
	FString google_email;

	UPROPERTY()
	FString user_name;

	UPROPERTY()
	FString password;

	UPROPERTY()
	int32 level;

	UPROPERTY()
	float cur_exp;
};

USTRUCT(BlueprintType)
struct FExpData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAp;
};

UCLASS(Blueprintable)
class ARKNIGHTS_API UUserDataManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UHttpSystem* m_httpSystem;

	UPROPERTY()
	FExpData m_expData;

	UPROPERTY()
	FUserData m_userData;

public:
	UUserDataManager();

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	void RequestUserData();

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	void OnRequestUserDataReceived(bool IsSuccess, FString respons);

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	void SetUserData(FString userDataJson);

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	void SetExpData(int32 level);

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	FString GetUserName() const;

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	int32 GetUserLevel() const;

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	float GetExpPercent();

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	int32 GetCurAp() const;

	UFUNCTION(BlueprintCallable, Category = "UserDataManager")
	int32 GetMaxAp() const;
};
