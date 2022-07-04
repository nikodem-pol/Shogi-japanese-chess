#pragma once
#include <SFML\Graphics.hpp>
#include <chrono>
#include <memory>
#include <string>
#include <mutex>

namespace fs = std::filesystem;

class FontManager
{
	sf::Font font;
	static std::shared_ptr<FontManager> instance_;
	static std::mutex mutex_;

protected:
	FontManager()
	{
		font.loadFromFile("fonts/arial.ttf");
	}
public:
	FontManager(FontManager& fn) = delete;
	void operator=(const FontManager&) = delete;
	static std::shared_ptr<FontManager> getInstance();
	sf::Font& getFont()
	{
		return font;
	}
};


