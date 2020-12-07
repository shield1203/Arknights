#pragma once

#include "CoreMinimal.h"
#include "UnitComponent.h"
#include "Operator.h"
#include "Engine/DataTable.h"
#include "OperatorComponent.generated.h"

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
	EOperatorUnitFlipbook FlipbookState;

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



UCLASS()
class ARKNIGHTS_API UOperatorComponent : public UUnitComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	EOperatorUnitFlipbook m_curState;

	UPROPERTY()
	TMap<EOperatorUnitFlipbook, FFlipbookInfo> m_flipbooks;

public:
	UOperatorComponent();

	void Start(EOperatorCode operatorCode);

	void SetFlipbookTransform(float x, float y, float z);

	void WithDraw();
};
