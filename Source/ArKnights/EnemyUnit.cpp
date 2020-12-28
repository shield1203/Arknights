#include "EnemyUnit.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.h"
#include "TowerBlock.h"
#include "EnemyComponent.h"
#include "TimerManager.h"
#include "OperationGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AEnemyUnit::AEnemyUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	m_curHP = 1.0f;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyUnitSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_collisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	m_collisionBoxComponent->SetupAttachment(RootComponent);

	m_enemyComponent = CreateDefaultSubobject<UEnemyComponent>(TEXT("EnemyComponent"));
	m_enemyComponent->SetupAttachment(RootComponent);
	m_enemyComponent->OnUnitDieCallback.BindUFunction(this, FName("UnitDestroy"));
	m_enemyComponent->OnUnitAttackCallback.BindUFunction(this, FName("UnitAttack"));

	m_HPBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHPBarComponent"));
	m_HPBarComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UHPBarWidget> HPBarWidget(TEXT("/Game/Widget/Operation/WB_EnemyHPBar"));
	if (HPBarWidget.Succeeded())
	{
		m_HPBarComponent->SetWidgetClass(HPBarWidget.Class);
	}
	m_HPBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBarComponent->SetDrawSize(FVector2D(126.0f, 7.0f));

	m_enemyData = CreateDefaultSubobject<UEnemy>(TEXT("EnemyUnitData"));
}

void AEnemyUnit::BeginPlay()
{
	Super::BeginPlay();

	UHPBarWidget* pHPBarWidget = Cast<UHPBarWidget>(m_HPBarComponent->GetUserWidgetObject());
	if (pHPBarWidget)
	{
		pHPBarWidget->SetOwningActor(this);
	}

	m_HPBarComponent->SetVisibility(false);
}

void AEnemyUnit::Initialize(EEnemyCode enemyCode, TArray<float>DestinationXPos, TArray<float>DestinationYPos, TArray<float>HoldingTime)
{
	m_enemyData->Initialize(enemyCode);
	m_maxHP = m_enemyData->GetMaxHP();
	m_curHP = m_maxHP;
	m_boxLocationX = m_enemyData->GetBoxLocationX();
	m_boxWidth = m_enemyData->GetBoxWidth();
	m_boxHeight = m_enemyData->GetBoxHeight();

	m_enemyComponent->LoadFlipbookData(enemyCode);
	m_destinationXPos = DestinationXPos;
	m_destinationYPos = DestinationYPos;
	m_holdingTime = HoldingTime;

	m_enemyComponent->FadeIn(true);
	m_enemyComponent->BlackIn(false);
}

void AEnemyUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_enemyComponent->UpdateAnimation();

	if (!m_life) return;

	if (CheckCollision()) return;

	if (!m_holding)
	{
		MoveToLocation();
	}

	CheckDestination();
}

bool AEnemyUnit::IsLife() const
{
	return m_life;
}

float AEnemyUnit::GetCurHP()
{
	if (m_life)
	{
		return m_curHP / m_enemyData->GetMaxHP();
	}

	return 0;
}

void AEnemyUnit::MoveToLocation()
{
	m_enemyComponent->SetFlipbookState(EEnemyUnitFlipbook::Move);
	
	float fTheta = FMath::Atan2(m_destinationYPos[m_destinationIndex] - GetActorLocation().Y, m_destinationXPos[m_destinationIndex] - GetActorLocation().X);
	if (FVector::Distance(FVector(m_destinationXPos[m_destinationIndex], m_destinationYPos[m_destinationIndex], GetActorLocation().Z), GetActorLocation()) <= m_enemyData->GetSpeed())
	{
		SetActorLocation(FVector(m_destinationXPos[m_destinationIndex], m_destinationYPos[m_destinationIndex], GetActorLocation().Z));
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
	}

	m_enemyComponent->SetComponentTransform();
	SetCollisionBoxTransform();
	SetHPBarTransform();
}

void AEnemyUnit::SetCollisionBoxTransform()
{
	m_collisionBoxComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	m_collisionBoxComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	m_collisionBoxComponent->SetBoxExtent(FVector(m_boxWidth, m_boxHeight, 0.5f));
	m_collisionBoxComponent->SetRelativeLocation(FVector(m_boxLocationX, 0.f, 66.f));
}

void AEnemyUnit::SetHPBarTransform()
{
	m_HPBarComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, -180.0f));
	m_HPBarComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 66.0f));
}

void AEnemyUnit::CheckDestination()
{
	if (!m_destinationXPos.IsValidIndex(m_destinationIndex))
	{
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
		UnitDie();
	}
}

void AEnemyUnit::CancelToHolding()
{
	m_holding = false;
}

bool AEnemyUnit::CheckCollision()
{
	if (m_targetUnit)
	{
		if (m_targetUnit->IsPlacementOperator())
		{
			return true;
		}
		else
		{
			m_targetUnit = nullptr;
			m_holding = false;
			return false;
		}
	}

	TSet<UPrimitiveComponent*>pOverlappingComponents;
	m_collisionBoxComponent->GetOverlappingComponents(pOverlappingComponents);
	
	for (auto overlappingComponent : pOverlappingComponents)
	{
		ATowerBlock* pTowerBlock = Cast<ATowerBlock>(overlappingComponent->GetOwner());
		if (overlappingComponent->GetName() == TEXT("CollisionCapsuleComponent") && pTowerBlock && pTowerBlock->CanBlock())
		{
			m_targetUnit = pTowerBlock;
			m_targetUnit->AddBlockUnit();
			m_enemyComponent->SetFlipbookState(EEnemyUnitFlipbook::Attack);
			m_holding = true;
			return true;
		}
	}
	
	return false;
}

void AEnemyUnit::EnemyDamaged(float Damage)
{
	m_HPBarComponent->SetVisibility(true);

	m_curHP -= Damage;
	m_enemyComponent->UnitDamageColor();

	if (m_curHP <= 0) UnitDie();
}

void AEnemyUnit::UnitAttack()
{
	if (m_targetUnit)
	{
		m_targetUnit->OperatorDamaged(m_enemyData->GetAtk());
	}
}

void AEnemyUnit::UnitDie()
{
	m_life = false;
	m_enemyComponent->SetFlipbookState(EEnemyUnitFlipbook::Die);
	m_enemyComponent->FadeIn(false);
	m_enemyComponent->BlackIn(true);
	m_collisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_holding = true;

	m_HPBarComponent->SetVisibility(false);

	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AOperationGameMode* GameMode = Cast<AOperationGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (GameMode)
		{
			GameMode->AddRemoveEnemyCount();
			if (m_curHP > 0)
			{
				GameMode->MinusLifePoint();
			}
		}
	}

	if (m_targetUnit)
	{
		m_targetUnit->RemoveBlockUnit();
	}
}

void AEnemyUnit::UnitDestroy()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		AOperationGameMode* GameMode = Cast<AOperationGameMode>(UGameplayStatics::GetGameMode(pWorld));
		if (GameMode)
		{
			GameMode->CheckOperationComplete();
		}
	}

	Destroy();
}