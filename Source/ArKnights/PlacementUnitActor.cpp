#include "PlacementUnitActor.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "ArKnightsGameInstance.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Operator.h"
#include "OperatorComponent.h"
#include "UObject/ConstructorHelpers.h"

APlacementUnitActor::APlacementUnitActor()
{
	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("PlacementUnitSceneComponent"));
	RootComponent = m_sceneCompoent;

	GetRenderComponent()->SetupAttachment(RootComponent);
	GetRenderComponent()->SetReceivesDecals(false);

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Blueprint/MT_Range.MT_Range'"));
	if (Material.Succeeded()) 
	{
		m_materialInstance = Material.Object;
	}
}

void APlacementUnitActor::Initialize(UOperator* operatorData)
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	m_operatorData = operatorData;
	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->GetRowNames().Num(); i++)
	{
		FOperatorFlipbookData* pFlipbookData = pGameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->FindRow<FOperatorFlipbookData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (operatorData->GetOperatorCode() == pFlipbookData->OperatorCode && EOperatorUnitFlipbook::Idle == pFlipbookData->FlipbookState)
		{
			UPaperFlipbook*  pUnitFlipbook = LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
			GetRenderComponent()->SetFlipbook(pUnitFlipbook);
			m_x = pFlipbookData->X;
			m_y = pFlipbookData->Y;
			m_z = pFlipbookData->Z;
			SetFlipbookLocation(m_x, m_y, m_z);
			break;
		}
	}

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperatorRangeData)->GetRowNames().Num(); i++)
	{
		FOperatorRange* pRangeData = pGameInstance->GetDataTable(EGameDataTable::OperatorRangeData)->FindRow<FOperatorRange>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (operatorData->GetOperatorCode() == pRangeData->Code)
		{	
			UDecalComponent* pRangeDecalComponent = NewObject<UDecalComponent>(this, UDecalComponent::StaticClass());

			if (pRangeDecalComponent == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Component nullptr"));
			}
			else
			{
				pRangeDecalComponent->SetupAttachment(RootComponent);
				pRangeDecalComponent->RegisterComponentWithWorld(pWorld);
				pRangeDecalComponent->SetDecalMaterial(m_materialInstance);
				pRangeDecalComponent->DecalSize = FVector(128.0f, 256.0f, 256.0f);
				pRangeDecalComponent->SetRelativeScale3D(FVector(1.f, 0.196f, 0.196f));
				pRangeDecalComponent->SetRelativeRotation(FRotator(270.f, 0.0f, 0.0f).Quaternion());
				pRangeDecalComponent->SetRelativeLocation(FVector(pRangeData->YRange * 100, pRangeData->XRange * 100, 0));

				m_decalComponents.Add(pRangeDecalComponent, FVector2D(pRangeData->YRange * 100, pRangeData->XRange * 100));
			}
		}
	}
}

void APlacementUnitActor::SetFlipbookLocation(float x, float y, float z)
{
	FVector flipbookScale = FVector(0.35f);
	GetRenderComponent()->SetRelativeScale3D(flipbookScale);

	//FRotator fliopbookRotation = FRotator(0, 0.0f, -80.0f);
	FRotator fliopbookRotation = FRotator(0, 90.0f, -80.0f);
	GetRenderComponent()->SetRelativeRotation(fliopbookRotation);

	FVector flipbookLocation = FVector(x, y, z);
	GetRenderComponent()->SetRelativeLocation(flipbookLocation);
}

void APlacementUnitActor::SetUnitLocation(FVector DestLocation, bool onTowerBlock)
{
	SetActorLocation(DestLocation);
	SetFlipbookLocation(m_x, m_y, m_z);

	for (auto decalComponent : m_decalComponents)
	{
		decalComponent.Key->SetVisibility(onTowerBlock);
		decalComponent.Key->SetRelativeLocation(FVector(decalComponent.Value, 0));
	}
}

void APlacementUnitActor::BeginDestroy()
{
	Super::BeginDestroy();
	m_operatorData = nullptr;
}

UOperator* APlacementUnitActor::GetOperatorData()
{
	return m_operatorData;
}