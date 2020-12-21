#include "TowerBlock.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "ArKnightsGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "OperatorComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "OperationSpectator.h"
#include "Kismet/GameplayStatics.h"

ATowerBlock::ATowerBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("TowerBlockSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBlockStaticMeshComponent"));
	m_staticMeshComponent->SetupAttachment(RootComponent);
	m_staticMeshComponent->CreateDynamicMaterialInstance(0);

	m_operatorComponent = CreateDefaultSubobject<UOperatorComponent>(TEXT("TowerBlockOperatorComponent"));
	m_operatorComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Blueprint/MT_Range.MT_Range'"));
	if (Material.Succeeded()) {
		m_materialInstance = Material.Object;
	}

	m_HPBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TowerBlockHPBarComponent"));
	m_HPBarComponent->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FClassFinder<UUserWidget> HPBarWidget(TEXT("/Game/Widget/Operation/WB_OperatorHPBar"));
	if (HPBarWidget.Succeeded())
	{
		m_HPBarComponent->SetWidgetClass(HPBarWidget.Class);
	}

	m_HPBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBarComponent->SetDrawSize(FVector2D(160.0f, 10.0f));
	m_HPBarComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, -180.0f));
	m_HPBarComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 51.0f));
	m_HPBarComponent->SetVisibility(false);
	m_HPBarComponent->RegisterComponent();
}

void ATowerBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATowerBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckPreparePlacement())
	{
		AppearPlacementBlock(DeltaTime);
	}
	else
	{
		m_staticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), m_InitColor);
	}

	if (m_operatorData)
	{
		m_HPBarComponent->SetVisibility(true);
		m_operatorComponent->UpdateAnimation();
	}
	else
	{
		m_HPBarComponent->SetVisibility(false);
	}
}

bool ATowerBlock::CanPlacement(EOperatorClass operatorClass)
{
	if (m_operatorData) return false;

	ETowerBlockType Type;

	switch (operatorClass)
	{
	case EOperatorClass::Vanguard:
	case EOperatorClass::Guard:
	case EOperatorClass::Defender:
	case EOperatorClass::Specialist: Type = ETowerBlockType::DownBlock; break;
	default: Type = ETowerBlockType::UpBlock;
	}

	if (m_type == Type) return true;
		
	return false;
}

bool ATowerBlock::CheckPreparePlacement()
{
	if (m_operatorData) return false;

	AOperationSpectator* pPlayer = Cast<AOperationSpectator>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (pPlayer == nullptr) return false;

	if (pPlayer->IsSelectedOperatorButton() && CanPlacement(pPlayer->GetSelectedOperatorClass()))
	{
		return true;
	}

	return false;
}

void ATowerBlock::AppearPlacementBlock(float DeltaTime)
{
	m_ferpPercent += DeltaTime;

	FVector ChangeColor;
	if (m_turnColor)
	{
		ChangeColor = FVector(FMath::Lerp(m_InitColor.X, m_ResultColor.X, m_ferpPercent), FMath::Lerp(m_InitColor.Y, m_ResultColor.Y, m_ferpPercent), FMath::Lerp(m_InitColor.Z, m_ResultColor.Z, m_ferpPercent));
	}
	else
	{
		ChangeColor = FVector(FMath::Lerp(m_ResultColor.X, m_InitColor.X, m_ferpPercent), FMath::Lerp(m_ResultColor.Y, m_InitColor.Y, m_ferpPercent), FMath::Lerp(m_ResultColor.Z, m_InitColor.Z, m_ferpPercent));
	}

	m_staticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), ChangeColor);

	if (m_ferpPercent >= 1.0f)
	{
		m_ferpPercent = 0.0f;

		m_turnColor = m_turnColor ? false : true;
	}
}

void ATowerBlock::StartPlacement(UOperator* operatorData)
{
	if (m_operatorData != nullptr) return;

	m_operatorData = operatorData;

	m_operatorComponent->Start(m_operatorData->GetOperatorCode());
}
