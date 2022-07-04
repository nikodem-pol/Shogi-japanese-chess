#pragma once
#include <optional>
#include "SFML/Graphics.hpp"
#include "FontManager.h"

class PromotingWidget : public sf::Drawable
{
	sf::Vector2f backgroundSize = { 150, 80 },
		otherSquaresSize = { 140,30 };
	sf::RectangleShape backgroundSquare, promoteFigureSquare, declinePromotionSquare;
	sf::Text promoteText, declineText;
	bool hidden;

public:
	PromotingWidget(sf::Vector2f position, std::string option1, std::string option2);
	~PromotingWidget() = default;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	std::optional<bool> getDecision(sf::Vector2i mousePos);


};

