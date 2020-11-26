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

UCLASS()
class ARKNIGHTS_API AOperatorUnit : public AUnitBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	EOperatorUnitState m_state;
	
public:
	AOperatorUnit();
};
