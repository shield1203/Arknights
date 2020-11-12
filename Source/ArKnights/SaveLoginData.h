#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveLoginData.generated.h"

UCLASS(BlueprintType)
class ARKNIGHTS_API USaveLoginData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FString userId;

	UPROPERTY()
	FString userEmail;

	USaveLoginData();
};