#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSignUpResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUserIdResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoginResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOperatorResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTeamResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShopGoodsResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPurchaseResponsReceivedDelegate, bool, bIsSuccess, FString, respons);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOperationResponsReceivedDelegate, bool, bIsSuccess, FString, respons);

UCLASS(BlueprintType)
class ARKNIGHTS_API UHttpSystem : public UObject
{
	GENERATED_BODY()
	
private:
	static const FString g_serverIP;

	FString m_serverConnectCheck;

	FHttpModule* m_httpModule;

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FSignUpResponsReceivedDelegate OnSignUpResponsReceivedCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FUserIdResponsReceivedDelegate OnUserIdResponsReceivedCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FLoginResponsReceivedDelegate OnLoginResponsReceivedCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FItemResponsReceivedDelegate OnItemResponsReceiveCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FOperatorResponsReceivedDelegate OnOperatorResponsReceiveCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FTeamResponsReceivedDelegate OnTeamResponsReceiveCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FShopGoodsResponsReceivedDelegate OnShopGoodsResponsReceiveCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FPurchaseResponsReceivedDelegate OnPurchaseResponsReceiveCallback;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "HttpSystem")
	FOperationResponsReceivedDelegate OnOperationResponsReceiveCallback;

public:
	UHttpSystem();

	// 로그인 아이디 체크
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestCheckArKnightsEmail(FString email, FString pw);

	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestCheckGoogleEmail(FString googleEmail);

	void OnCheckEmailResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 회원가입
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestSignUp(FString email, FString pw);

	void OnSignUpResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 로그인
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestLogin(FString id);

	void OnLoginResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 아이템 목록
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestItems(FString id);

	void OnItemResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 오퍼레이터 목록
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestOperators(FString id);

	void OnOperatorResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 팀 목록
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestTeams(FString id);

	void OnTeamResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 팀 수정 요청
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestTeamChange(FString id, FString teamJson);

	// 상점 아이템 목록
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestShopGoods(FString id, FString menu);

	void OnShopGoodsResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 아이템 구매
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestPurchase(FString id, FString menu, FString number);

	void OnPurchaseResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 클리어 작전 조회
	UFUNCTION(BlueprintCallable, Category = "HttpSystem")
	void RequestOperation(FString id);

	void OnOperationResponsReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};