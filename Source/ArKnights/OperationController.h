#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OperationController.generated.h"

UCLASS()
class ARKNIGHTS_API AOperationController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnUnitControllPressed();
	void OnUnitControllReleased();

public:
	AOperationController();
};