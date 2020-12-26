#include "TowerBlock.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "ArKnightsGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.h"
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

	m_collisionCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsuleComponent"));
	m_collisionCapsuleComponent->SetupAttachment(RootComponent);
	m_collisionCapsuleComponent->SetCapsuleRadius(38.f);
	m_collisionCapsuleComponent->SetCapsuleHalfHeight(80.f);
	m_collisionCapsuleComponent->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	m_collisionCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_operatorComponent = CreateDefaultSubobject<UOperatorComponent>(TEXT("TowerBlockOperatorComponent"));
	m_operatorComponent->SetupAttachment(RootComponent);
	m_operatorComponent->OnUnitAttackCallback.BindUFunction(this, FName("UnitAttack"));
	m_operatorComponent->OnUnitDieCallback.BindUFunction(this, FName("UnitWithdraw"));

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Blueprint/MT_Range.MT_Range'"));
	if (Material.Succeeded()) {
		m_materialInstance = Material.Object;
	}

	m_HPBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TowerBlockHPBarComponent"));
	m_HPBarComponent->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FClassFinder<UHPBarWidget> HPBarWidget(TEXT("/Game/Widget/Operation/WB_OperatorHPBar"));
	if (HPBarWidget.Succeeded())
	{
		m_HPBarComponent->SetWidgetClass(HPBarWidget.Class);
	}

	m_HPBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_HPBarComponent->SetDrawSize(FVector2D(160.0f, 10.0f));
	m_HPBarComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, -180.0f));
	m_HPBarComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 51.0f));
	m_HPBarComponent->RegisterComponent();	
}

void ATowerBlock::BeginPlay()
{
	Super::BeginPlay();
	
	UHPBarWidget* pHPBarWidget = Cast<UHPBarWidget>(m_HPBarComponent->GetUserWidgetObject());
	if (pHPBarWidget)
	{
		pHPBarWidget->SetOwningActor(this);
	}

	m_HPBarComponent->SetVisibility(false);
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

	m_operatorComponent->UpdateAnimation();
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
	m_operatorCurHP = m_operatorData->GetMaxHP();

	m_operatorComponent->Start(m_operatorData->GetOperatorCode());

	m_collisionCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	m_HPBarComponent->SetVisibility(true);
}

float ATowerBlock::GetCurHP()
{
	if (m_operatorData)
	{
		return m_operatorCurHP / m_operatorData->GetMaxHP();
	}

	return 0;
}

bool ATowerBlock::IsPlacementOperator()
{
	if (m_operatorData) return true;

	return false;
}

bool ATowerBlock::CanBlock()
{
	bool bCanBlock;
	bCanBlock = (m_operatorData && m_operatorData->GetBlock() > m_blockUnit && m_type == ETowerBlockType::DownBlock) ? true : false;
	
	return bCanBlock;
}

void ATowerBlock::AddBlockUnit()
{
	m_blockUnit++;
}

void ATowerBlock::RemoveBlockUnit()
{
	m_blockUnit--;
}

void ATowerBlock::UnitAttack()
{

}

void ATowerBlock::OperatorDamaged(float Damage)
{
	m_operatorCurHP -= Damage;
	m_operatorComponent->UnitDamageColor();

	if (m_operatorCurHP <= 0) UnitDie();
}

void ATowerBlock::UnitDie()
{
	m_operatorData = nullptr;
	m_operatorComponent->SetFlipbookState(EOperatorUnitFlipbook::Die);
	m_collisionCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_HPBarComponent->SetVisibility(false);
}

void ATowerBlock::UnitWithdraw()
{
	// 유닛 선택 블록 리스트에 복귀, 딜레이 카운트 포함
	m_operatorComponent->RemoveFlipbookData();
}