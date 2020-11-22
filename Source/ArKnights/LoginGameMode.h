#pragma once

#include "CoreMinimal.h"
#include "ArKnightsGameModeBase.h"
#include "LoginGameMode.generated.h"

UCLASS()
class ARKNIGHTS_API ALoginGameMode : public AArKnightsGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay();

public:
	ALoginGameMode();

	UFUNCTION(BlueprintCallable)
	void SaveLoginData(FString Email, FString id);

	UFUNCTION(BlueprintCallable)
	void LoadLoginData(FString& Email, FString& id);
};
