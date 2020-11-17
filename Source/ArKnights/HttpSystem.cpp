#include "HttpSystem.h"

//const FString UHttpSystem::g_serverIP = TEXT("203.232.193.170:3000"); // 연구실 LAN
const FString UHttpSystem::g_serverIP = TEXT("192.168.0.29:3000"); // 연구실 WiFi_DBLAB
//const FString UHttpSystem::g_serverIP = TEXT("192.168.0.59:3000"); // 연구실 WIFI_iptime

UHttpSystem::UHttpSystem()
{
	m_httpModule = &FHttpModule::Get();

	m_serverConnectCheck = TEXT("서버접속 실패. 다시 시도해주십시오.");
}

void UHttpSystem::RequestCheckArKnightsEmail(FString email, FString pw)
{
	FString strScheme = TEXT("/CheckArknightsEmail?email=") + email + TEXT("&password=") + pw;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnCheckEmailResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::RequestCheckGoogleEmail(FString googleEmail)
{
	FString strScheme = TEXT("/CheckGoogleEmail?googleEmail=") + googleEmail;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnCheckEmailResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnCheckEmailResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		if (Response->GetContentAsString() == "check_fail")
		{
			bWasSuccessful = false;
			strResult = TEXT("로그인에 실패하였습니다.");
		}
		else
		{
			strResult = Response->GetContentAsString();
		}
	}

	OnUserIdResponsReceivedCallback.Broadcast(bWasSuccessful, strResult);
}

void UHttpSystem::RequestSignUp(FString email, FString pw)
{
	FString strScheme = TEXT("/SignUp?email=") + email + TEXT("&password=") + pw;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnSignUpResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnSignUpResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		if (Response->GetContentAsString() == "signUp_fail")
		{
			bWasSuccessful = false;
			strResult = TEXT("이미 존재하는 이메일입니다.");
		}
		else
		{
			strResult = Response->GetContentAsString();
		}
	}

	OnSignUpResponsReceivedCallback.Broadcast(bWasSuccessful, strResult);
}

void UHttpSystem::RequestLogin(FString id)
{
	FString strScheme = TEXT("/Login?id=") + id;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnLoginResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnLoginResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful && Response->GetContentAsString() == "login_fail")
	{
		bWasSuccessful = false;
		strResult = TEXT("로그인 실패.");
	}

	if (bWasSuccessful)
	{
		OnLoginResponsReceivedCallback.Broadcast(bWasSuccessful, Response->GetContentAsString());
	}
	else
	{
		OnLoginResponsReceivedCallback.Broadcast(bWasSuccessful, strResult);
	}
}

void UHttpSystem::RequestItems(FString id)
{
	FString strScheme = TEXT("/Items?id=") + id;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnItemResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnItemResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		strResult = Response->GetContentAsString();
	}

	OnItemResponsReceiveCallback.Broadcast(bWasSuccessful, strResult);
}

void UHttpSystem::RequestOperators(FString id)
{
	FString strScheme = TEXT("/Operators?id=") + id;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnOperatorResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnOperatorResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		strResult = Response->GetContentAsString();
	}

	OnOperatorResponsReceiveCallback.Broadcast(bWasSuccessful, strResult);
}

void UHttpSystem::RequestTeams(FString id)
{
	FString strScheme = TEXT("/Teams?id=") + id;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnTeamResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnTeamResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		strResult = Response->GetContentAsString();
	}

	OnTeamResponsReceiveCallback.Broadcast(bWasSuccessful, strResult);
}

void UHttpSystem::RequestTeamChange(FString id, FString teamJson)
{
	FString strScheme = TEXT("/TeamsChange?id=") + id;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	HttpRequest->SetURL(strURL);
	HttpRequest->SetContentAsString(teamJson);

	HttpRequest->ProcessRequest();
}

void UHttpSystem::RequestShopGoods(FString id, FString menu)
{
	FString strScheme = TEXT("/Shop?id=") + id + TEXT("&menu=") + menu;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnShopGoodsResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnShopGoodsResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		strResult = Response->GetContentAsString();
	}

	OnShopGoodsResponsReceiveCallback.Broadcast(bWasSuccessful, strResult);
}

void UHttpSystem::RequestPurchase(FString id, FString menu, FString number)
{
	FString strScheme = TEXT("/Purchase?id=") + id + TEXT("&menu=") + menu + TEXT("&number=") + number;
	FString strURL = g_serverIP + strScheme;

	TSharedPtr<IHttpRequest> HttpRequest = m_httpModule->CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(strURL);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpSystem::OnPurchaseResponsReceived);
	HttpRequest->ProcessRequest();
}

void UHttpSystem::OnPurchaseResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString strResult = m_serverConnectCheck;

	if (bWasSuccessful)
	{
		strResult = Response->GetContentAsString();
	}

	OnPurchaseResponsReceiveCallback.Broadcast(bWasSuccessful, strResult);
}