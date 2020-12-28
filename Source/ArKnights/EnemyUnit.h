#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemyUnit.generated.h"

class ATowerBlock;

UCLASS()
class ARKNIGHTS_API AEnemyUnit : public AActor
{
	GENERATED_BODY()
	
protected:	
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY()
	class UBoxComponent* m_collisionBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UEnemyComponent* m_enemyComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* m_HPBarComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemy* m_enemyData;

	UPROPERTY()
	ATowerBlock* m_targetUnit;

	UPROPERTY()
	bool m_life = true;

	UPROPERTY()
	float m_maxHP;

	UPROPERTY()
	float m_curHP;

	UPROPERTY()
	float m_boxLocationX;

	UPROPERTY()
	float m_boxWidth;

	UPROPERTY()
	float m_boxHeight;

	FTimerHandle m_holdingTimerHandle;

	int32 m_destinationIndex = 0;

	UPROPERTY()
	TArray<float>m_destinationXPos;

	UPROPERTY()
	TArray<float>m_destinationYPos;

	UPROPERTY()
	TArray<float>m_holdingTime;

	UPROPERTY()
	bool m_holding = false;

protected:
	virtual void BeginPlay() override;

public:	
	AEnemyUnit();

	void Initialize(EEnemyCode enemyCode, TArray<float>DestinationXPos, TArray<float>DestinationYPos, TArray<float>HoldingTime);

	virtual void Tick(float DeltaTime) override;

	bool IsLife() const;

	UFUNCTION(BlueprintCallable)
	float GetCurHP();

	void MoveToLocation();

	void SetCollisionBoxTransform();

	void SetHPBarTransform();

	void CheckDestination();

	void CancelToHolding();

	bool CheckCollision();

	void EnemyDamaged(float Damage);

	UFUNCTION()
	void UnitAttack();

	UFUNCTION()
	void UnitDie();

	UFUNCTION()
	void UnitDestroy();
};
