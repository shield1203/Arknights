#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerBlock.generated.h"

UCLASS()
class ARKNIGHTS_API ATowerBlock : public APawn
{
	GENERATED_BODY()

private:
	

protected:
	virtual void BeginPlay() override;

public:	
	ATowerBlock();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};