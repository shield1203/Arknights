#pragma once

#include "CoreMinimal.h"
#include "ArKnightsGameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class ARKNIGHTS_API ALobbyGameMode : public AArKnightsGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay();

public:
	ALobbyGameMode();

	UFUNCTION(BlueprintCallable)
	void RequestLobbyData();
};
