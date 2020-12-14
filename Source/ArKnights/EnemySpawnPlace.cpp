#include "EnemySpawnPlace.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyUnit.h"

AEnemySpawnPlace::AEnemySpawnPlace()
{
	PrimaryActorTick.bCanEverTick = false;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemySpawnStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);

	m_staticMeshComponent->SetRelativeLocation(FVector(0, 0, 100.0f));
}

void AEnemySpawnPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemySpawnPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AEnemySpawnPlace::GetPlaceNum()
{
	return m_placeNum;
}

void AEnemySpawnPlace::SpawnEnemy(EEnemyCode enemyCode, TArray<float>DestinationXPos, TArray<float>DestinationYPos, TArray<float>HoldingTime)
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		AEnemyUnit* pSpawnEnemy = pWorld->SpawnActor<AEnemyUnit>(GetActorLocation(), FRotator(0), SpawnParams);
		pSpawnEnemy->Initialize(enemyCode, DestinationXPos, DestinationYPos, HoldingTime);
	}
}