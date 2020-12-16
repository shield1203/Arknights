#include "EnemyUnit.h"
#include "Components/SceneComponent.h"
#include "EnemyComponent.h"
#include "TimerManager.h"

AEnemyUnit::AEnemyUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyUnitSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_enemyComponent = CreateDefaultSubobject<UEnemyComponent>(TEXT("EnemyComponent"));
	m_enemyComponent->SetupAttachment(RootComponent);

	m_enemyData = CreateDefaultSubobject<UEnemy>(TEXT("EnemyUnitData"));
}

void AEnemyUnit::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyUnit::Initialize(EEnemyCode enemyCode, TArray<float>DestinationXPos, TArray<float>DestinationYPos, TArray<float>HoldingTime)
{
	m_enemyData->Initialize(enemyCode);
	m_enemyComponent->LoadFlipbookData(enemyCode);
	m_destinationXPos = DestinationXPos;
	m_destinationYPos = DestinationYPos;
	m_holdingTime = HoldingTime;

	m_enemyComponent->FadeIn(true);
}

void AEnemyUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_holding)
	{
		MoveToLocation();
	}

	CheckDestination();
}

void AEnemyUnit::MoveToLocation()
{
	m_enemyComponent->SetFlipbookState(EEnemyUnitFlipbook::Move);
	
	float fTheta = FMath::Atan2(m_destinationYPos[m_destinationIndex] - GetActorLocation().Y, m_destinationXPos[m_destinationIndex] - GetActorLocation().X);
	if (FVector::Distance(FVector(m_destinationXPos[m_destinationIndex], m_destinationYPos[m_destinationIndex], GetActorLocation().Z), GetActorLocation()) <= m_enemyData->GetSpeed())
	{
		SetActorLocation(FVector(m_destinationXPos[m_destinationIndex], m_destinationYPos[m_destinationIndex], GetActorLocation().Z));
		UE_LOG(LogTemp, Warning, TEXT("%f"), FVector::Distance(FVector(m_destinationXPos[m_destinationIndex], m_destinationYPos[m_destinationIndex], GetActorLocation().Z), GetActorLocation()));
	}
	else
	{
		FVector nextLocation = GetActorLocation();
		nextLocation.X += (FMath::Cos(fTheta) * m_enemyData->GetSpeed());
		nextLocation.Y += (FMath::Sin(fTheta) * m_enemyData->GetSpeed());

		if (FMath::Abs(m_destinationXPos[m_destinationIndex] - nextLocation.X) <= m_enemyData->GetSpeed())
		{
			nextLocation.X = m_destinationXPos[m_destinationIndex];
		}

		if (FMath::Abs(m_destinationYPos[m_destinationIndex] - nextLocation.Y) <= m_enemyData->GetSpeed())
		{
			nextLocation.Y = m_destinationYPos[m_destinationIndex];
		}
		
		SetActorLocation(nextLocation);

		if (FMath::Cos(fTheta) == 0 && FMath::Sin(fTheta) == 0)
		{
			nextLocation.X += m_enemyData->GetSpeed();
			nextLocation.Y += m_enemyData->GetSpeed();
		}

		UE_LOG(LogTemp, Warning, TEXT("Theta : %f"), fTheta);
		UE_LOG(LogTemp, Warning, TEXT("X : %f, Y : %f"), nextLocation.X, nextLocation.Y);
		UE_LOG(LogTemp, Warning, TEXT("Cos : %f, Sin : %f"), (FMath::Cos(fTheta)), (FMath::Sin(fTheta)));
		UE_LOG(LogTemp, Warning, TEXT("XSpeed : %f, YSpeed : %f"), (FMath::Cos(fTheta) * m_enemyData->GetSpeed()), (FMath::Sin(fTheta) * m_enemyData->GetSpeed()));

		if (m_enemyData->GetSpeed() == 0)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("Speed : %f"), m_enemyData->GetSpeed());
			UE_LOG(LogTemp, Warning, TEXT("MaxHP : %f"), m_enemyData->GetMaxHP());*/
		}
	}

	m_enemyComponent->SetComponentTransform();
}

void AEnemyUnit::CheckDestination()
{
	if (!m_destinationXPos.IsValidIndex(m_destinationIndex))
	{
		m_enemyComponent->SetFlipbookState(EEnemyUnitFlipbook::Idle);
		m_holding = true;
		return;
	}

	FVector ActorLocation = GetActorLocation();
	if (m_destinationXPos[m_destinationIndex] == ActorLocation.X && m_destinationYPos[m_destinationIndex] == ActorLocation.Y)
	{
		if (m_holdingTime[m_destinationIndex] >= 1.f)
		{
			GetWorldTimerManager().SetTimer(m_holdingTimerHandle, this, &AEnemyUnit::CancelToHolding, m_holdingTime[m_destinationIndex], false);
			m_enemyComponent->SetFlipbookState(EEnemyUnitFlipbook::Idle);
			m_holding = true;
		}
		m_destinationIndex++;
	}

	if (m_destinationXPos.Num() <= m_destinationIndex)
	{
		Destroy();
	}
}

void AEnemyUnit::CancelToHolding()
{
	m_holding = false;
}