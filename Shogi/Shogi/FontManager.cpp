#include "FontManager.h"

std::shared_ptr <FontManager> FontManager::instance_ = nullptr;
std::mutex FontManager::mutex_;

std::shared_ptr<FontManager> FontManager::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);

	if (instance_ == nullptr)
	{
		instance_.reset(new FontManager);
	}
	return instance_;
}