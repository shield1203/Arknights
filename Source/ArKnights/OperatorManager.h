#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Operator.h"
#include "OperatorManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTeamUpdateDelegate);

UENUM(BlueprintType)
enum class EOperatorSort : uint8
{
	Level UMETA(DisplayName = "OperatorSort_Level"),
	Rarity UMETA(DisplayName = "OperatorSort_Rarity"),
	Reliability UMETA(DisplayName = "OperatorSort_Reliability"),
	Name UMETA(DisplayName = "OperatorSort_Name"),
};

USTRUCT()
struct FOperatorInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint32 operator_num;

	UPROPERTY()
	uint64 owner_id;

	UPROPERTY()
	EOperatorCode operator_code;

	UPROPERTY()
	int32 level;

	UPROPERTY()
	float cur_exp;
	
	UPROPERTY()
	int32 rank;

	UPROPERTY()
	int32 potential_ability;

	UPROPERTY()
	int32 reliability;
};

USTRUCT(BlueprintType)
struct FTeamInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString TeamName;

	UPROPERTY()
	TArray<int32> Member;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API UOperatorManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UHttpSystem* m_httpSystem;

	UPROPERTY()
	TMap<EOperatorCode, UOperator*> m_operators;

	UPROPERTY()
	EOperatorSort m_sortType;

	UPROPERTY()
	bool m_ascendingOrder;

	UPROPERTY()
	TArray<FTeamInfo> m_teams;

	UPROPERTY()
	int32 m_selectedTeamNum;

	UPROPERTY()
	int32 m_maxTeamNum;

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "OperatorManager")
	FTeamUpdateDelegate OnTeamUpdateCallback;

public:
	UOperatorManager();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void RequestOperators();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void OnOperatorResponsRecived(bool IsSuccess, FString respons);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void RequestTeams();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void OnTeamResponsRecived(bool IsSuccess, FString respons);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void RequestTeamChange();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetOperators(FString operators);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetSortType(EOperatorSort sortType);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void ToggleAscendingOrder();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetSelectedTeamNum(int32 selectNum);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetPrevTeamNum();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetNextTeamNum();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetTeams(FString teams);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SetTeamName(FString newName);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void AddMemeber(int32 operatorCode);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void ChangeMemeber(int32 oldMemberCode, int32 newMemberCode);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TMap<EOperatorCode, UOperator*> GetOperators();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	EOperatorSort GetSortType() const;

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	bool IsAscendingOrder() const;

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SortOperatorToLevel();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SortOperatorToRarity();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SortOperatorToReliability();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	void SortOperatorToName();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	int32 GetSelectedTeamNum() const;

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	FString GetTeamJsonString();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	FString GetTeamName(int32 teamNum);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TArray<UOperator*> GetCurTeamMember();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TArray<UOperator*> GetOperationMember();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TArray<UOperator*> GetExceptCurTeamMember();
};