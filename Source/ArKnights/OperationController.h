#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OperationController.generated.h"

UCLASS()
class ARKNIGHTS_API AOperationController : public APlayerController
{
	GENERATED_BODY()
	
private:
	FHitResult m_hit;

	ETouchIndex::Type m_touchIndex;

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnUnitControllPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnUnitControllReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

public:
	AOperationController();
};