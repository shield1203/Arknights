#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArKnightsGameModeBase.generated.h"

UCLASS()
class ARKNIGHTS_API AArKnightsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GameModeBase", meta = (AllowPrivateAccess = "true"))
	class UUserWidget* m_mainWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "GameModeBase", meta = (AllowPrivateAccess = "true"))
	class USoundSystem* m_soundSystem;

public:
	AArKnightsGameModeBase();

	UFUNCTION(BlueprintCallable)
	void SetMainWidget();

	UFUNCTION(BlueprintCallable)
	void AddToViewSubWidgets();
};
