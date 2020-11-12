#include "Item.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Templates/SharedPointer.h"
#include "ArKnightsGameInstance.h"

UItem::UItem()
{
}

void UItem::Initialize(EItemCode code, int32 amount, int32 price, bool soldOut)
{
	m_code = code;
	m_amount = amount;
	m_price = price;
	m_soldOut = soldOut;

	LoadItemData(code);
}

void UItem::LoadItemData(EItemCode itemCode)
{
	UWorld* pWorld = GetWorld();

	UArKnightsGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UArKnightsGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance nullptr"));
		return;
	}

	FItemData* pItemData = pGameInstance->GetDataTable(EGameDataTable::ItemData)->FindRow<FItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(itemCode)))), FString(""));

	FString strGrade = TEXT("/Game/Resource/item/");
	switch (pItemData->Grade)
	{
	case EItemGrade::Gold: strGrade += TEXT("Grade_Gold"); break;
	case EItemGrade::Pink: strGrade += TEXT("Grade_Pink"); break;
	case EItemGrade::Blue: strGrade += TEXT("Grade_Blue"); break;
	case EItemGrade::Yellow: strGrade += TEXT("Grade_Yellow"); break;
	case EItemGrade::Gray: strGrade += TEXT("Grade_Gray"); break;
	}

	m_data.Type = pItemData->Type;
	m_data.Name = pItemData->Name;
	m_image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pItemData->Image)));
	m_grade = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(strGrade)));
	m_data.Description1 = pItemData->Description1;
	m_data.Description2 = pItemData->Description2;
}

int32 UItem::GetAmount() const
{
	return m_amount;
}

int32 UItem::GetPrice() const
{
	return m_price;
}

bool UItem::IsSoldOut() const
{
	return m_soldOut;
}

UTexture2D* UItem::GetImage() const
{
	return m_image;
}

UTexture2D* UItem::GetGrade() const
{
	return m_grade;
}

EItemType UItem::GetType() const
{
	return m_data.Type;
}

FString UItem::GetName() const
{
	return m_data.Name;
}

FString UItem::GetDescription1() const
{
	return m_data.Description1;
}

FString UItem::GetDescription2() const
{
	return m_data.Description2;
}