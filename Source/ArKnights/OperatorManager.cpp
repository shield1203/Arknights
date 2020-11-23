#include "OperatorManager.h"
#include "ArKnightsGameInstance.h"
#include "ArKnights_Keys.h"
#include "SaveLoginData.h"
#include "Kismet/GameplayStatics.h"
#include "HttpSystem.h"
#include "JsonObjectConverter.h"

UOperatorManager::UOperatorManager()
{
	m_sortType = EOperatorSort::Level;
	m_ascendingOrder = false;

	m_selectedTeamNum = 0;
	
	m_httpSystem = CreateDefaultSubobject<UHttpSystem>(TEXT("OperatorManager_HttpSystem"));
	m_httpSystem->OnOperatorResponsReceiveCallback.AddDynamic(this, &UOperatorManager::OnOperatorResponsRecived);
	m_httpSystem->OnTeamResponsReceiveCallback.AddDynamic(this, &UOperatorManager::OnTeamResponsRecived);

	m_maxTeamNum = 4;
	for (uint8 i = 0; i < m_maxTeamNum; i++)
	{
		FTeamInfo emptyTeam;
		emptyTeam.TeamName = TEXT("Unknown");
		m_teams.Add(emptyTeam);
	}
}

void UOperatorManager::RequestOperators()
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));

	m_httpSystem->RequestOperators(loginData->userId);
}

void UOperatorManager::OnOperatorResponsRecived(bool IsSuccess, FString respons)
{
	if (IsSuccess)
	{
		SetOperators(respons);
	}
}

void UOperatorManager::RequestTeams()
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));

	m_httpSystem->RequestTeams(loginData->userId);
}

void UOperatorManager::OnTeamResponsRecived(bool IsSuccess, FString respons)
{
	if (IsSuccess)
	{
		SetTeams(respons);
	}
}

void UOperatorManager::RequestTeamChange()
{
	auto loginData = Cast<USaveLoginData>(UGameplayStatics::LoadGameFromSlot(login_keys::login_data_slot_name, 0));

	m_httpSystem->RequestTeamChange(loginData->userId, GetTeamJsonString());
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
		pAddOperator->Initialize(operatorData.operator_code, operatorData.level, operatorData.cur_exp, operatorData.rank, operatorData.potential_ability, operatorData.reliability);
		m_operators.Add(operatorData.operator_code, pAddOperator);
	}
}

void UOperatorManager::SetSortType(EOperatorSort sortType)
{
	if (m_sortType == sortType)
	{
		ToggleAscendingOrder();
	}
	else
	{
		m_sortType = sortType;
	}
}

void UOperatorManager::ToggleAscendingOrder()
{
	m_ascendingOrder = m_ascendingOrder ? false : true;
}

void UOperatorManager::SetSelectedTeamNum(int32 selectNum)
{
	m_selectedTeamNum = selectNum;
}

void UOperatorManager::SetPrevTeamNum()
{
	m_selectedTeamNum -= 1;

	if (m_selectedTeamNum < 0)
	{
		m_selectedTeamNum = m_maxTeamNum - 1;
	}
}

void UOperatorManager::SetNextTeamNum()
{
	m_selectedTeamNum++;
	m_selectedTeamNum %= m_maxTeamNum;
}

void UOperatorManager::SetTeams(FString teams)
{
	if (teams == "") return;

	if (!FJsonObjectConverter::JsonArrayStringToUStruct(teams, &m_teams, 0, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Json noting"));
		return;
	}
}

void UOperatorManager::SetTeamName(FString newName)
{
	m_teams[m_selectedTeamNum].TeamName = newName;
}

void UOperatorManager::AddMemeber(int32 operatorCode)
{
	m_teams[m_selectedTeamNum].Member.Add(operatorCode);
}

void UOperatorManager::ChangeMemeber(int32 oldMemberCode, int32 newMemberCode)
{
	for (auto &member : m_teams[m_selectedTeamNum].Member)
	{
		if (member == oldMemberCode)
		{
			member = newMemberCode;
		}
	}
}

TMap<EOperatorCode, UOperator*> UOperatorManager::GetOperators()
{
	switch (m_sortType)
	{
	case EOperatorSort::Level: SortOperatorToLevel(); break;
	case EOperatorSort::Rarity: SortOperatorToRarity(); break;
	case EOperatorSort::Reliability: SortOperatorToReliability(); break;
	case EOperatorSort::Name: SortOperatorToName(); break;
	}

	return m_operators;
}

EOperatorSort UOperatorManager::GetSortType() const
{
	return m_sortType;
}

bool UOperatorManager::IsAscendingOrder() const
{
	return m_ascendingOrder;
}

void UOperatorManager::SortOperatorToLevel()
{
	if (m_ascendingOrder)
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetLevel() < B.GetLevel();
		});
	}
	else
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetLevel() > B.GetLevel();
			});
	}
}

void UOperatorManager::SortOperatorToRarity()
{
	if (m_ascendingOrder)
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetRarity() < B.GetRarity();
			});
	}
	else
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetRarity() > B.GetRarity();
			});
	}
}

void UOperatorManager::SortOperatorToReliability()
{
	if (m_ascendingOrder)
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetReliability() < B.GetReliability();
			});
	}
	else
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetReliability() > B.GetReliability();
			});
	}
}

void UOperatorManager::SortOperatorToName()
{
	if (m_ascendingOrder)
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetName().Compare(B.GetName()) < 0;
			});
	}
	else
	{
		m_operators.ValueSort([](const UOperator& A, const UOperator& B) {
			return A.GetName().Compare(B.GetName()) > 0;
			});
	}
}

int32 UOperatorManager::GetSelectedTeamNum() const
{
	return m_selectedTeamNum;
}

FString UOperatorManager::GetTeamJsonString()
{
	FString TeamJsonString = TEXT("[");

	int32 maxTeam = 3;
	for (int32 i = 0; i <= maxTeam; i++)
	{
		FString JsonObjectString;
		FJsonObjectConverter::UStructToJsonObjectString(m_teams[i], JsonObjectString, 0, 0);

		TeamJsonString += JsonObjectString;

		if (i == maxTeam)
		{
			TeamJsonString += TEXT("]");
		}
		else
		{
			TeamJsonString += TEXT(",");
		}
	}

	return TeamJsonString;
}

FString UOperatorManager::GetTeamName(int32 teamNum)
{
	return m_teams[teamNum].TeamName;
}

TArray<UOperator*> UOperatorManager::GetCurTeamMember()
{
	TArray<UOperator*> teamMember;

	for (auto member : m_teams[m_selectedTeamNum].Member)
	{
		teamMember.Add(m_operators[static_cast<EOperatorCode>(member)]);
	}

	return teamMember;
}

TArray<UOperator*> UOperatorManager::GetExceptCurTeamMember()
{
	TArray<UOperator*> ExceptedMember;

	for (auto myOperator : m_operators)
	{
		bool bExcept = false;
		for (auto member : m_teams[m_selectedTeamNum].Member)
		{
			if (myOperator.Key == static_cast<EOperatorCode>(member))
			{
				bExcept = true;
				break;
			}
		}

		if (!bExcept)
		{
			ExceptedMember.Add(myOperator.Value);
		}
	}

	return ExceptedMember;
}