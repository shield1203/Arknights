#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "UnitComponent.generated.h"

DECLARE_DELEGATE(FOnUnitAttackDelegate);
DECLARE_DELEGATE(FOnUnitDieDelegate);

UENUM(BlueprintType)
enum class EUnitState : uint8
{
	Start UMETA(DisplayName = "Unit_Start"),
	Idle UMETA(DisplayName = "Unit_Idle"),
	Move UMETA(DisplayName = "Unit_Move"),
	Attack UMETA(DisplayName = "Unit_Attack"),
	Skill UMETA(DisplayName = "Unit_Skill"),
	Die UMETA(DisplayName = "Unit_Die"),
};

UENUM(BlueprintType)
enum class ESightDerection : uint8
{
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
};

UENUM(BlueprintType)
enum class EUnitForm : uint8
{
	Front UMETA(DisplayName = "Front"),
	Back UMETA(DisplayName = "Back"),
};

USTRUCT()
struct FFlipbookInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 frame;

	UPROPERTY()
	float X;

	UPROPERTY()
	float Y;

	UPROPERTY()
	float Z;

	UPROPERTY()
	class UPaperFlipbook* Flipbook;
};

UCLASS()
class ARKNIGHTS_API UUnitComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	EUnitState m_state;

	UPROPERTY()
	ESightDerection m_sightt;

	UPROPERTY()
	EUnitForm m_form;

	UPROPERTY()
	bool m_upAlphaValue;

	UPROPERTY()
	bool m_upBlackValue;

	UPROPERTY()
	FLinearColor m_color;

protected:
	FTimerHandle m_alphaTimerHandle;

	FTimerDynamicDelegate m_delegateChangeAlphaValue;

	FTimerHandle m_blackTimerHandle;

	FTimerDynamicDelegate m_delegateChangeBlackValue;

	FTimerHandle m_damageColorTimerHandle;

	FTimerDynamicDelegate m_delegateChangeColorValue;

public:
	FOnUnitAttackDelegate OnUnitAttackCallback;

	FOnUnitDieDelegate OnUnitDieCallback;

public:
	UUnitComponent();

	virtual void UpdateAnimation() {};

	virtual void CheckFrameEvent() {};

	void SetInitColor();

	void FadeIn(bool upAlphaValue);

	UFUNCTION()
	void ChangeAlphaValue();

	void BlackIn(bool upBlackValue);

	UFUNCTION()
	void ChangeBlackValue();

	void UnitDamageColor();

	UFUNCTION()
	void ChangeColorValue();
};
