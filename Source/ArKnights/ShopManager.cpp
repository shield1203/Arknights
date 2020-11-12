#include "ShopManager.h"
#include "JsonObjectConverter.h"
#include "Arknights_keys.h"

UShopManager::UShopManager()
{
}

FString UShopManager::GetMenuKey(EShopMenu shopMenu)
{
	FString keyString = "";

	switch (shopMenu)
	{
	case EShopMenu::Orundum: keyString = shop_menu_keys::originite_prime; break;
	case EShopMenu::Credit: keyString = shop_menu_keys::credit; break;
	}

	return keyString;
}

void UShopManager::SetOriginite_Prime_Goods(FString originite_Priem_Goods)
{
	m_originitePrimeGoods.Empty();

	if (originite_Priem_Goods == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("goods noting"));
		return;
	}

	if (!FJsonObjectConverter::JsonArrayStringToUStruct(originite_Priem_Goods, &m_originitePrimeGoods, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}
}

void UShopManager::SetCredit_Goods(FString credit_Goods)
{
	m_creditGoods.Empty();

	if (credit_Goods == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("goods noting"));
		return;
	}

	TArray<FCredit_Goods> creditGoods;
	if (!FJsonObjectConverter::JsonArrayStringToUStruct(credit_Goods, &creditGoods, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}

	for (auto itemData : creditGoods)
	{
		UItem* pAddItem = NewObject<UItem>(this, UItem::StaticClass());
		pAddItem->Initialize(itemData.itemCode, itemData.amount, itemData.price, itemData.sold_out);
		UE_LOG(LogTemp, Warning, TEXT("itemCode : %d, amount : %d, price : %d"), itemData.itemCode, itemData.amount, itemData.price);
		m_creditGoods.Add(pAddItem);
	}
}

TArray<FOriginite_Prime_Goods> UShopManager::GetOriginitePrimeGoods()
{
	return m_originitePrimeGoods;
}

TArray<UItem*> UShopManager::GetCreditGoods()
{
	return m_creditGoods;
}