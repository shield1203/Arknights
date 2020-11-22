#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace login_keys
{
	TCHAR const* const login_data_slot_name = TEXT("loginData");
}

namespace data_table_keys
{
	TCHAR const* const tip = TEXT("/Game/DataTable/Tip");
	TCHAR const* const item = TEXT("/Game/DataTable/Item");
	TCHAR const* const opertator = TEXT("/Game/DataTable/Operator");
	TCHAR const* const exp = TEXT("/Game/DataTable/Exp");
	TCHAR const* const operation = TEXT("/Game/DataTable/Operation");
}

namespace shop_menu_keys
{
	TCHAR const* const originite_prime = TEXT("Shop_Originite_Prime");
	TCHAR const* const credit = TEXT("Shop_Credit");
}