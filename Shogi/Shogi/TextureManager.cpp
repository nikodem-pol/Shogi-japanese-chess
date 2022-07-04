#include "TextureManager.h"

std::shared_ptr <TextureManager> TextureManager::instance_ = nullptr;
std::mutex TextureManager::mutex_;

std::shared_ptr<TextureManager> TextureManager::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);

	if (instance_ == nullptr)
	{
		instance_.reset(new TextureManager);
	}
	return instance_;
}