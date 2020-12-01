#pragma once

#include "CoreMinimal.h"
#include "UnitBase.h"
#include "Operator.h"
#include "Engine/DataTable.h"
#include "OperatorUnit.generated.h"



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
