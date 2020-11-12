#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundSystem.generated.h"

UENUM(BlueprintType)
enum class ESound_BGM : uint8
{
	Title UMETA(DisplayName = "BGM_Title"),
	Lobby UMETA(DisplayName = "BGM_Lobby"),
};

UCLASS(BlueprintType)
class ARKNIGHTS_API USoundSystem : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SoundSystem", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* m_audioComponentBGM;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SoundSystem", meta = (AllowPrivateAccess = "true"))
	TArray<class USoundCue*> m_soundCueBGM;
public:
	USoundSystem();

	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	void PlayBGM(ESound_BGM bgm);

	UFUNCTION(BlueprintCallable, Category = "SoundSystem")
	void StopBGM();
};
