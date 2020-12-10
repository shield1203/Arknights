// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class ARKNIGHTS_API ATestActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class USceneComponent* m_sceneCompoent;

	UPROPERTY()
	class UEnemyComponent* m_enemy;

	FVector m_location;

public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
