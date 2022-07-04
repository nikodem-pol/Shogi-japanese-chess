#pragma once
#include <optional>
#include "FontManager.h"
#include "SFML/Graphics.hpp"

class DecisionWindow : public sf::Drawable
{
	sf::RectangleShape backgroundRect, yesOptionRect, noOptionRect;
	sf::Text messegeText, yesText, noText;
public:
	DecisionWindow(sf::Vector2f pos, std::string messege);
	std::optional<bool> getDecision(sf::Vector2i mousePos);
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override
	{
		target.draw(backgroundRect, state);
		target.draw(yesOptionRect, state);
		target.draw(noOptionRect, state);
		target.draw(messegeText, state);
		target.draw(yesText, state);
		target.draw(noText, state);
	}

};

