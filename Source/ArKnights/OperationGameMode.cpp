#include "OperationGameMode.h"
#include "ArKnightsGameInstance.h"
#include "OperationManager.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

AOperationGameMode::AOperationGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> OperationWidget(TEXT("/Game/Widget/Operation/WB_Operation"));
	if (OperationWidget.Succeeded())
	{
		m_mainWidget = CreateWidget(GetWorld(), OperationWidget.Class);
	}
}

void AOperationGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;
	m_operationManager = pGameInstance->GetOperationManager();

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