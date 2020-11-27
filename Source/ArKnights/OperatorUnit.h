#pragma once

#include "CoreMinimal.h"
#include "UnitBase.h"
#include "Operator.h"
#include "Engine/DataTable.h"
#include "OperatorUnit.generated.h"

UENUM(BlueprintType)
enum class EOperatorUnitState : uint8
{
	Start UMETA(DisplayName = "Unit_Start"),
	Idle UMETA(DisplayName = "Unit_Idle"),
	Attack UMETA(DisplayName = "Unit_Attack"),
	Skill UMETA(DisplayName = "Unit_Skill"),
	Die UMETA(DisplayName = "Unit_Die"),
};

USTRUCT(BlueprintType)
struct FOperatorFlipbookData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EOperatorCode OperatorCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Frame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CenterX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CenterY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path;
};

USTRUCT(BlueprintType)
struct FOperatorFlipbook
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 frame;

	UPROPERTY()
	int32 x;

	UPROPERTY()
	int32 y;

	UPROPERTY()
	class UPaperFlipbook* Animation;
};

UCLASS()
class ARKNIGHTS_API AOperatorUnit : public AUnitBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	EOperatorUnitState m_state;
	
	UPROPERTY()
	TArray<FOperatorFlipbook>m_frontFlipbook;

	UPROPERTY()
	TArray<FOperatorFlipbook>m_backFlipbook;

	class UPaperFlipbook* m_animation;

	virtual void BeginPlay() override;

public:
	AOperatorUnit();

	virtual void Initialize();

	void LoadFlipbookData();

	UFUNCTION(BlueprintCallable)
	void SetUnitState(EOperatorUnitState state);
};
