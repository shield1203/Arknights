#pragma once

#include "CoreMinimal.h"
#include "UnitComponent.h"
#include "Enemy.h"
#include "Engine/DataTable.h"
#include "EnemyComponent.generated.h"

UENUM(BlueprintType)
enum class EEnemyUnitFlipbook : uint8
{
	Idle UMETA(DisplayName = "Flipbook_Idle"),
	Attack UMETA(DisplayName = "Flipbook_Attack"),
	Move UMETA(DisplayName = "Flipbook_Move"),
	Die UMETA(DisplayName = "Flipbook_Die"),
};

USTRUCT(BlueprintType)
struct FEnemyFlipbookData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyCode EnemyCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyUnitFlipbook FlipbookState;

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
class ARKNIGHTS_API UEnemyComponent : public UUnitComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	EEnemyUnitFlipbook m_curState;

	UPROPERTY()
	TMap<EEnemyUnitFlipbook, FFlipbookInfo> m_flipbooks;

public:
	UEnemyComponent();

	virtual void UpdateAnimation();

	virtual void CheckFrameEvent();

	void LoadFlipbookData(EEnemyCode enemyCode);

	void SetFlipbookState(EEnemyUnitFlipbook unitState);

	void SetComponentTransform();
};
