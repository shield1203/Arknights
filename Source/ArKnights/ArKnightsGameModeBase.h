#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArKnightsGameModeBase.generated.h"

UCLASS()
class ARKNIGHTS_API AArKnightsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_UMG", meta = (AllowPrivateAccess = "true"))
	TArray<class UUserWidget*> m_widgets;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_SoundSystem", meta = (AllowPrivateAccess = "true"))
	class USoundSystem* m_soundSystem;

public:
	AArKnightsGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "Game_UMG")
	void AddWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Game_UMG")
	void RemoveLastWidget();
};
