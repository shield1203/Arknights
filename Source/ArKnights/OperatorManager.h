#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Operator.h"
#include "OperatorManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTeamUpdateDelegate);

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
	uint32 level;

	UPROPERTY()
	uint64 cur_exp;
	
	UPROPERTY()
	uint32 rank;

	UPROPERTY()
	uint8 potential_ability;

	UPROPERTY()
	uint32 reliability;
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
	TArray<FTeamInfo> m_teams;

	UPROPERTY()
	int32 m_selectedTeamNum;

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
	int32 GetSelectedTeamNum() const;

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	FString GetTeamJsonString();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	FString GetTeamName(int32 teamNum);

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TArray<UOperator*> GetCurTeamMember();

	UFUNCTION(BlueprintCallable, Category = "OperatorManager")
	TArray<UOperator*> GetExceptCurTeamMember();
};