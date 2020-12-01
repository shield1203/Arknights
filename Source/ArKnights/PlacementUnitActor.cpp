#include "PlacementUnitActor.h"
#include "Components/SceneComponent.h"
#include "ArKnightsGameInstance.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "OperatorComponent.h"

APlacementUnitActor::APlacementUnitActor()
{
	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("PlacementUnitSceneComponent"));
	RootComponent = m_sceneCompoent;

	GetRenderComponent()->SetupAttachment(RootComponent);
}

void APlacementUnitActor::Initialize(EOperatorCode operatorCode)
{
	UWorld* pWorld = GetWorld();
	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	for (int32 i = 0; i < pGameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->GetRowNames().Num(); i++)
	{
		FOperatorFlipbookData* pFlipbookData = pGameInstance->GetDataTable(EGameDataTable::OperatorFlipbookData)->FindRow<FOperatorFlipbookData>(FName(*(FString::FormatAsNumber(i))), FString(""));
		if (operatorCode == pFlipbookData->OperatorCode && EOperatorUnitFlipbook::Idle == pFlipbookData->FlipbookState)
		{
			UPaperFlipbook*  pUnitFlipbook = LoadObject<UPaperFlipbook>(this, *pFlipbookData->Path);
			GetRenderComponent()->SetFlipbook(pUnitFlipbook);
			SetFlipbookLocation(pFlipbookData->X, pFlipbookData->Y, pFlipbookData->Z);
			UE_LOG(LogTemp, Warning, TEXT("Clear Filpbook"));
			return;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%d, %d"), pFlipbookData->OperatorCode, pFlipbookData->FlipbookState);
		}
	}
}

void APlacementUnitActor::SetFlipbookLocation(float x, float y, float z)
{
	FVector flipbookScale = FVector(0.35f);
	GetRenderComponent()->SetRelativeScale3D(flipbookScale);

	FRotator fliopbookRotation = FRotator(0, 90.0f, -80.0f);
	GetRenderComponent()->SetRelativeRotation(fliopbookRotation);

	FVector flipbookLocation = FVector(x, y, z);
	GetRenderComponent()->SetRelativeLocation(flipbookLocation);
}