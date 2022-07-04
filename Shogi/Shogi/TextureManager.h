#pragma once
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <filesystem>
#include <utility>
#include <chrono>
#include <memory>
#include <string>
#include <mutex>

namespace fs = std::filesystem;

class TextureManager
{
	std::unordered_map<std::string, sf::Texture> textures;

	static std::shared_ptr<TextureManager> instance_;
	static std::mutex mutex_;

protected:
	TextureManager()
	{
		fs::path images("images");
		sf::Texture tx;
		std::string txName;

		for (auto& entry : fs::directory_iterator(images))
		{
			tx.loadFromFile(entry.path().string());
			txName = entry.path().stem().string();
			textures.emplace(txName, tx);
		}
	}
public:
	TextureManager(TextureManager& tx) = delete;
	void operator=(const TextureManager&) = delete;
	static std::shared_ptr<TextureManager> getInstance();
	sf::Texture& getTx(std::string txName)
	{
		return textures[txName];
	}
};


