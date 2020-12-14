#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "UnitComponent.generated.h"

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

	FTimerHandle m_changeAlphaTimerHandle;

	float m_preAlphaValue;

	float m_nextAlphaValue;

public:
	UUnitComponent();

	virtual void UpdateAnimation() {};

	void FadeIn();

	void FadeOut();

	void ChangeAlphaValue();
};
