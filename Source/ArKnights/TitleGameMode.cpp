#include "TitleGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "SoundSystem.h"

ATitleGameMode::ATitleGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidget(TEXT("/Game/Widget/Title/WB_Title"));
	if (TitleWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), TitleWidget.Class);
	}
}

void ATitleGameMode::StartPlay()
{
	Super::StartPlay();

	SetMainWidget();
}