#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "UnitBase.generated.h"

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
enum class ERangeDerection : uint8
{
	North UMETA(DisplayName = "North"),
	South UMETA(DisplayName = "South"),
	West UMETA(DisplayName = "West"),
	East UMETA(DisplayName = "East"),
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

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API AUnitBase : public APaperCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	ESightDerection m_sightt;

public:
	AUnitBase();

	virtual void UpdateAnimation() {};
};