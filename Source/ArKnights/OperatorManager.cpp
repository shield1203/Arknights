#include "OperatorManager.h"
#include "JsonObjectConverter.h"

UOperatorManager::UOperatorManager()
{
}

void UOperatorManager::SetOperators(FString operators)
{
	m_operators.Reset();

	if (operators == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("operator noting"));
		return;
	}

	TArray<FOperatorInfo> operatorInfo;
	if (!FJsonObjectConverter::JsonArrayStringToUStruct(operators, &operatorInfo, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}

	for (auto operatorData : operatorInfo)
	{
		UOperator* pAddOperator = NewObject<UOperator>(this, UOperator::StaticClass());
		pAddOperator->Initialize(operatorData.operator_code, operatorData.level);
		m_operators.Add(operatorData.operator_code, pAddOperator);
	}
}

TMap<EOperatorCode, UOperator*> UOperatorManager::GetOperators()
{
	return m_operators;
}