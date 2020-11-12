#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class ARKNIGHTS_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	float m_roll = 0.1f;

	UPROPERTY(EditAnywhere)
	float m_pitch = 0.1f;

	UPROPERTY(EditAnywhere)
	float m_yaw = 0.1f;

protected:
	virtual void BeginPlay() override;

public:	
	ARotatingActor();

	virtual void Tick(float DeltaTime) override;
};
