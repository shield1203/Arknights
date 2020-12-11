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

AOperationGameMode::AOperationGameMode()
{
	PlayerControllerClass = AOperationController::StaticClass();
	SpectatorClass = AOperationSpectator::StaticClass();
	DefaultPawnClass = AOperationSpectator::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> OperationWidget(TEXT("/Game/Widget/Operation/WB_Loading"));
	if (OperationWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), OperationWidget.Class);
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

	SetMainWidget();
	GetWorldTimerManager().SetTimer(m_costTimerHandle, this, &AOperationGameMode::AddCostGauge, 0.02, true);
}

int32 AOperationGameMode::GetCurCost() const
{
	return m_curCost;
}

float AOperationGameMode::GetCostGauge() const
{
	return m_costGauge;
}

void AOperationGameMode::AddCost(int32 value)
{
	m_curCost += value;	

	m_curCost = (m_curCost > 99) ? 99 : m_curCost;
}

void AOperationGameMode::AddCostGauge()
{
	if (m_curCost >= 99) return;

	m_costGauge += 0.02;

	if (m_costGauge >= 1)
	{
		AddCost(1);
		m_costGauge -= 1;
	}
}

void AOperationGameMode::AddDieEnemyCount()
{
	m_dieEnemyCount += 1;
}