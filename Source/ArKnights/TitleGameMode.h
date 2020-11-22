#pragma once

#include "CoreMinimal.h"
#include "ArKnightsGameModeBase.h"
#include "TitleGameMode.generated.h"

UCLASS()
class ARKNIGHTS_API ATitleGameMode : public AArKnightsGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay();

public:
	ATitleGameMode();
};
