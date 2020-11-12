#include "SoundSystem.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"

USoundSystem::USoundSystem()
{
	m_audioComponentBGM = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundSystemBGM"));
	m_audioComponentBGM->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundCue> TitleBGM(TEXT("SoundCue'/Game/Sound/titleBGM_Cue.titleBGM_Cue'"));
	if (TitleBGM.Succeeded())
	{
		m_soundCueBGM.Add(TitleBGM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> LobbyBGM(TEXT("SoundCue'/Game/Sound/lobbyBGM_Cue.lobbyBGM_Cue'"));
	if (LobbyBGM.Succeeded())
	{
		m_soundCueBGM.Add(LobbyBGM.Object);
	}
}

void USoundSystem::PlayBGM(ESound_BGM bgm)
{
	if (!m_soundCueBGM.IsValidIndex(static_cast<uint8>(bgm))) return;

	m_audioComponentBGM->SetSound(m_soundCueBGM[static_cast<uint8>(bgm)]);
	m_audioComponentBGM->Play();
}

void USoundSystem::StopBGM()
{
	if (m_audioComponentBGM->IsPlaying())
	{
		m_audioComponentBGM->Stop();
	}
}