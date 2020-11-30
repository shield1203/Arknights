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
}

void AOperatorUnit::Initialize()
{
	m_animation = LoadObject<UPaperFlipbook>(this, TEXT("/Game/Flipbook/Hoshiguma/Hoshiguma_idle"));
	GetSprite()->SetFlipbook(m_animation);

	SetUnitVector();
}

void AOperatorUnit::LoadFlipbookData()
{

}

void AOperatorUnit::SetUnitVector()
{
	FVector scale;
	scale.X = 0.35;
	scale.Y = 0.35;
	scale.Z = 0.35;
	GetSprite()->SetRelativeScale3D(scale);

	FRotator rotator;
	rotator.Roll = -80.0f;
	rotator.Yaw = 90.0f;
	GetSprite()->SetRelativeRotation(rotator);

	FVector location;
	location.X = -12;
	location.Y = -7.95;
	location.Z = 20;
	GetSprite()->SetRelativeLocation(location);
}