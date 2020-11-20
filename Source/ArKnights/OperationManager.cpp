#include "OperationManager.h"

UOperationManager::UOperationManager()
{

}

void UOperationManager::SetEpisode(uint8 selectedEpisode)
{
	m_curEpisode = selectedEpisode;
}

void UOperationManager::SetChapter(uint8 selectedChapter)
{
	m_curChapter = selectedChapter;
}

uint8 UOperationManager::GetCurEpisode() const
{
	return m_curEpisode;
}

uint8 UOperationManager::GetCurChapter() const
{
	return m_curChapter;
}

uint8 UOperationManager::GetOperationClearRank(uint8 episode, uint8 chapter) const
{
	for (auto clearOperation : m_clearOperation)
	{
		if (episode == clearOperation.episode && chapter == clearOperation.chapter)
		{
			return clearOperation.clear_rank;
		}
	}

	return 0;
}