#include "WidgetManager.h"
#include "Blueprint/UserWidget.h"

UWidgetManager::UWidgetManager()
{

}

void UWidgetManager::SetMainWidget(UUserWidget* mainWidget)
{
	m_mainWidget = mainWidget;
	m_mainWidget->AddToViewport();
}

void UWidgetManager::AddSubWidget(UUserWidget* subWidget)
{
	m_subWidgets.Add(subWidget);
	subWidget->AddToViewport();
}

void UWidgetManager::RemoveSubWidget(UUserWidget* subWidget)
{
	m_subWidgets.Remove(subWidget);
	subWidget->RemoveFromParent();
}

void UWidgetManager::RemoveAllSubWidget()
{
	for (auto& subWidget : m_subWidgets)
	{
		subWidget->RemoveFromParent();
		m_subWidgets.Remove(subWidget);
	}
}

void UWidgetManager::AddToViewportSubWidgets()
{
	for (auto& subWidget : m_subWidgets)
	{
		subWidget->AddToViewport();
	}
}

void UWidgetManager::RemoveFromViewportSubWidgets()
{
	for (auto& subWidget : m_subWidgets)
	{
		subWidget->RemoveFromViewport();
	}
}