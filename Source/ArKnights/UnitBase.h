#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "UnitBase.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARKNIGHTS_API AUnitBase : public APaperCharacter
{
	GENERATED_BODY()
	
protected:


public:
	AUnitBase();
};
