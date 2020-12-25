#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

class UProgressBar;
class AActor;

UCLASS(HideDropdown)
class ARKNIGHTS_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Custom)
	AActor* m_owningActor;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* m_unitHPBar;

public:
	void SetOwningActor(AActor* OwningActor);
};
