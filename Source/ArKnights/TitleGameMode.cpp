#include "TitleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "SoundSystem.h"

ATitleGameMode::ATitleGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidget(TEXT("/Game/Widget/Title/WB_Title"));
	if (TitleWidget.Succeeded())
	{
		AddWidget(TitleWidget.Class);
	}
}