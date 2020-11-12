#include "RotatingActor.h"

ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FQuat quatRotator = FQuat(FRotator(m_pitch, m_yaw, m_roll));

	AddActorLocalRotation(quatRotator, false, 0, ETeleportType::None);
}

