#pragma once

#include "CoreMinimal.h"
#include "UnitBase.h"
#include "Operator.h"
#include "Engine/DataTable.h"
#include "OperatorUnit.generated.h"

UENUM(BlueprintType)
enum class EOperatorUnitFlipbook : uint8
{
	Start UMETA(DisplayName = "Flipbook_Start"),
	Start_Back UMETA(DisplayName = "Flipbook_Start_Back"),
	Idle UMETA(DisplayName = "Flipbook_Idle"),
	Idle_Back UMETA(DisplayName = "Flipbook_Idle_Back"),
	Attack UMETA(DisplayName = "Flipbook_Attack"),
	Attack_Back UMETA(DisplayName = "Flipbook_Attack_Back"),
	Attack_Down UMETA(DisplayName = "Flipbook_Attack_Down"),
	Die UMETA(DisplayName = "Flipbook_Die"),
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
	float X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Z;

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
	/*UPROPERTY()
	EOperatorUnitFlipbook m_filpbookState;
	
	UPROPERTY()
	TArray<FOperatorFlipbook>m_frontFlipbook;

	UPROPERTY()
	TArray<FOperatorFlipbook>m_backFlipbook;*/

	class UPaperFlipbook* m_animation;

	virtual void BeginPlay() override;

public:
	AOperatorUnit();

	virtual void Initialize();

	void LoadFlipbookData();

	void SetUnitVector();
};
