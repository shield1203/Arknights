#include "RangeDecalComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"
#include "EnemyUnit.h"

URangeDecalComponent::URangeDecalComponent()
{
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Blueprint/MT_Range.MT_Range'"));
	if (Material.Succeeded())
	{
		SetMaterial(0, Material.Object);
	}

	m_collisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	m_collisionBoxComponent->SetupAttachment(this);
	m_collisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_collisionBoxComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	m_collisionBoxComponent->SetBoxExtent(FVector(150.f, 250.f, 250.f));
}

UBoxComponent* URangeDecalComponent::GetCollisionBoxComponent() const
{
	return m_collisionBoxComponent;
}

void URangeDecalComponent::SetComponentTransform(int32 xPos, int32 yPos)
{
	DecalSize = FVector(128.0f, 256.0f, 256.0f);
	SetRelativeScale3D(FVector(1.f, 0.196f, 0.196f));
	SetRelativeRotation(FRotator(270.f, 0.0f, 0.0f).Quaternion());
	SetRelativeLocation(FVector(yPos * 100, xPos * 100, 50.f));

	m_collisionBoxComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	m_collisionBoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

AEnemyUnit* URangeDecalComponent::CheckCollision()
{
	TSet<UPrimitiveComponent*>pOverlappingComponents;
	m_collisionBoxComponent->GetOverlappingComponents(pOverlappingComponents);

	for (auto overlappingComponent : pOverlappingComponents)
	{
		AEnemyUnit* pEnemyUnit = Cast<AEnemyUnit>(overlappingComponent->GetOwner());
		if (pEnemyUnit && pEnemyUnit->IsLife())
		{		
			return pEnemyUnit;
		}
	}
	return nullptr;
}
