#include "OperatorUnit.h"
#include "PaperFlipbookComponent.h"
//#include "Kismet/GameplayStatics.h"
#include "PaperFlipbook.h"

AOperatorUnit::AOperatorUnit()
{

}

void AOperatorUnit::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void AOperatorUnit::Initialize()
{
	//m_animation = LoadObject<UPaperFlipbook>(this, TEXT("/Game/Flipbook/Hoshiguma/Hoshiguma_Attack_back"));
	//GetSprite()->SetFlipbook(m_animation);
}

void AOperatorUnit::LoadFlipbookData()
{

}