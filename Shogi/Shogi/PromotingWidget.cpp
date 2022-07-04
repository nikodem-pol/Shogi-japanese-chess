#include "PromotingWidget.h"

PromotingWidget::PromotingWidget(sf::Vector2f position, std::string option1, std::string option2) : hidden(true)
{
	auto fontManager = FontManager::getInstance();

	promoteText.setFont(fontManager->getFont());
	promoteText.setCharacterSize(24);
	promoteText.setFillColor(sf::Color::Black);
	//promoteText.setStyle(sf::Text::Bold);
	promoteText.setString(option1);

	declineText.setFont(fontManager->getFont());
	declineText.setCharacterSize(24);
	declineText.setFillColor(sf::Color::Black);
	//declineText.setStyle(sf::Text::Bold);
	declineText.setString(option2);

	backgroundSquare.setFillColor(sf::Color::Black);
	backgroundSquare.setOutlineColor(sf::Color::White);
	backgroundSquare.setOutlineThickness(2);
	backgroundSquare.setSize(backgroundSize);
	backgroundSquare.setOrigin(backgroundSize.x / 2, backgroundSize.y / 2);
	backgroundSquare.setPosition(position);

	promoteFigureSquare.setFillColor(sf::Color::White);
	promoteFigureSquare.setSize(otherSquaresSize);
	promoteFigureSquare.setOrigin(otherSquaresSize.x / 2, otherSquaresSize.y / 2);
	promoteFigureSquare.setPosition(position.x, position.y - backgroundSize.y / 4);

	//Centering "Promote" text
	auto promoteTextRect = promoteText.getLocalBounds();
	promoteText.setOrigin(promoteTextRect.left + promoteTextRect.width / 2,
		promoteTextRect.top + promoteTextRect.height / 2);
	promoteText.setPosition(promoteFigureSquare.getPosition());


	declinePromotionSquare.setFillColor(sf::Color::White);
	declinePromotionSquare.setSize(otherSquaresSize);
	declinePromotionSquare.setOrigin(otherSquaresSize.x / 2, otherSquaresSize.y / 2);
	declinePromotionSquare.setPosition(position.x, position.y + backgroundSize.y / 4);

	//Centering "Decline" text
	auto declineTextRect = promoteText.getLocalBounds();
	declineText.setOrigin(declineTextRect.left + declineTextRect.width / 2,
		declineTextRect.top + declineTextRect.height / 2);
	declineText.setPosition(declinePromotionSquare.getPosition());

}

void PromotingWidget::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(backgroundSquare, state);
	target.draw(promoteFigureSquare, state);
	target.draw(declinePromotionSquare, state);
	target.draw(promoteText, state);
	target.draw(declineText, state);
}

std::optional<bool> PromotingWidget::getDecision(sf::Vector2i mousePos)
{
	if (mousePos.x >= promoteFigureSquare.getPosition().x - otherSquaresSize.x / 2
		&& mousePos.x <= promoteFigureSquare.getPosition().x + otherSquaresSize.x / 2
		&& mousePos.y >= promoteFigureSquare.getPosition().y - otherSquaresSize.y / 2
		&& mousePos.y <= promoteFigureSquare.getPosition().y + otherSquaresSize.y / 2)
	{
		return { true };
	}
	else if (mousePos.x >= declinePromotionSquare.getPosition().x - otherSquaresSize.x / 2
		&& mousePos.x <= declinePromotionSquare.getPosition().x + otherSquaresSize.x / 2
		&& mousePos.y >= declinePromotionSquare.getPosition().y - otherSquaresSize.y / 2
		&& mousePos.y <= declinePromotionSquare.getPosition().y + otherSquaresSize.y / 2)
	{
		return { false };
	}
	else
	{
		return {};
	}
	
}