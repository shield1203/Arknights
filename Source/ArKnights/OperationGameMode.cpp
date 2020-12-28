#include "OperationGameMode.h"
#include "ArKnightsGameInstance.h"
#include "Operator.h"
#include "OperationManager.h"
#include "OperatorManager.h"
#include "OperationController.h"
#include "OperationSpectator.h"
#include "OperatorComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "PaperFlipbook.h"
#include "Enemy.h"
#include "EnemyComponent.h"
#include "EnemyManager.h"

AOperationGameMode::AOperationGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = AOperationController::StaticClass();
	SpectatorClass = AOperationSpectator::StaticClass();
	DefaultPawnClass = AOperationSpectator::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> OperationWidget(TEXT("/Game/Widget/Operation/WB_Loading"));
	if (OperationWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), OperationWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> OperationCompleteWidget(TEXT("/Game/Widget/Operation/WB_MissionComplete"));
	if (OperationCompleteWidget.Succeeded())
	{
		m_missionCompleteWidget = CreateWidget(GetWorld(), OperationCompleteWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> OperationFailedWidget(TEXT("/Game/Widget/Operation/WB_MissionFailed"));
	if (OperationFailedWidget.Succeeded())
	{
		m_missionFailedWidget = CreateWidget(GetWorld(), OperationFailedWidget.Class);
	}
}

void AOperationGameMode::Tick(float DeltaTime)
{
}

void AOperationGameMode::PreLoadFlipbookData()
{
	TArray<EOperatorCode>OperationMember;
	for (auto member : m_operatorManager->GetOperationMember())
	{
		OperationMember.Add(member->GetOperatorCode());
	}

	for (int32 i = 0; i < m_gameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->GetRowNames().Num(); i++)
	{
		FOperatorFlipbookData* pFlipbookData = m_gameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->FindRow<FOperatorFlipbookData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (OperationMember.Contains(pFlipbookData->OperatorCode))
		{
			LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
		}
	}

	TArray<EEnemyCode>OperationEnemy = m_enemyManager->GetOperationEnemy(m_operationManager->GetCurEpisode(), m_operationManager->GetCurChapter());
	for (int32 i = 0; i < m_gameInstance->GetDataTable(EGameDataTable::EnemyFlipbookData)->GetRowNames().Num(); i++)
	{
		FEnemyFlipbookData* pFlipbookData = m_gameInstance->GetDataTable(EGameDataTable::EnemyFlipbookData)->FindRow<FEnemyFlipbookData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (OperationEnemy.Contains(pFlipbookData->EnemyCode))
		{
			LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
		}
	}
}

void AOperationGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* pWorld = GetWorld();
	m_gameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!m_gameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	m_operationManager = m_gameInstance->GetOperationManager();
	m_operatorManager = m_gameInstance->GetOperatorManager();
	m_enemyManager = m_gameInstance->GetEnemyManager();

	m_lifePoint = m_operationManager->GetOperationLifePoint();
	m_enemyManager->LoadOperationEnemyData(m_operationManager->GetCurEpisode(), m_operationManager->GetCurChapter());
	
	SetMainWidget();
	GetWorldTimerManager().SetTimer(m_costTimerHandle, this, &AOperationGameMode::AddCostGauge, 0.02, true);
	GetWorldTimerManager().SetTimer(m_enemySpawnTimerHandle, this, &AOperationGameMode::CheckEnemySpawn, 0.1, true);
}

int32 AOperationGameMode::GetCurCost() const
{
	return m_curCost;
}

float AOperationGameMode::GetCostGauge() const
{
	return m_costGauge;
}

int32 AOperationGameMode::GetLifePoint() const
{
	return m_lifePoint;
}

int32 AOperationGameMode::GetRemoveEnemy() const
{
	return m_removeEnemyCount;
}

void AOperationGameMode::MinusLifePoint()
{
	m_lifePoint--;
	if (m_lifePoint == 0)
	{
		SetSubWidget(m_missionFailedWidget);
	}
}

void AOperationGameMode::AddCost(int32 value)
{
	m_curCost += value;	

	m_curCost = (m_curCost > 99) ? 99 : m_curCost;
}

void AOperationGameMode::AddCostGauge()
{
	if (m_curCost >= 99) return;

	m_costGauge += 0.02f;

	if (m_costGauge >= 1)
	{
		AddCost(1);
		m_costGauge -= 1;
	}
}

void AOperationGameMode::AddRemoveEnemyCount()
{
	m_removeEnemyCount++;	
}

void AOperationGameMode::CheckOperationComplete()
{
	if (m_removeEnemyCount == m_operationManager->GetOperationEnemies())
	{
		SetSubWidget(m_missionCompleteWidget);
	}
}

void AOperationGameMode::CheckEnemySpawn()
{
	m_enemyManager->CheckEnemySpawnTime(0.1f);
}