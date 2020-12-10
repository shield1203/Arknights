#include "TestActor.h"
#include "Components/SceneComponent.h"
#include "EnemyComponent.h"

ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("ckSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_enemy = CreateDefaultSubobject<UEnemyComponent>(TEXT("ckScenent"));
	m_enemy->SetupAttachment(RootComponent);
	m_enemy->Init();
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	m_location = FVector(-250.f, -350.f, 155.f);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_location.Y += (DeltaTime * 100);
	SetActorLocation(m_location);
	m_enemy->SetRelativeRotation(FRotator(0, 90.0f, -80.0f));
	m_enemy->SetRelativeScale3D(FVector(0.35f, 0.35f, 0.35f));

	if (m_location.Y >= 0)
	{
		m_enemy->SetLooping(false);
	}
}

