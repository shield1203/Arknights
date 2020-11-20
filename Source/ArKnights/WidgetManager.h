#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetManager.generated.h"

UCLASS()
class ARKNIGHTS_API UWidgetManager : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WidgetManager")
	UUserWidget* m_mainWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WidgetManager")
	TArray<UUserWidget*> m_subWidgets;

public:
	UWidgetManager();
	
	UFUNCTION(BlueprintCallable, Category = "WidgetManager")
	void SetMainWidget(UUserWidget* mainWidget);

	UFUNCTION(BlueprintCallable, Category = "WidgetManager")
	void AddSubWidget(UUserWidget* subWidget);

	UFUNCTION(BlueprintCallable, Category = "WidgetManager")
	void RemoveSubWidget(UUserWidget* subWidget);

	UFUNCTION(BlueprintCallable, Category = "WidgetManager")
	void RemoveAllSubWidget();

	UFUNCTION(BlueprintCallable, Category = "WidgetManager")
	void AddToViewportSubWidgets();

	UFUNCTION(BlueprintCallable, Category = "WidgetManager")
	void RemoveFromViewportSubWidgets();
};
