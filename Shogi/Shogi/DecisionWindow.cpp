#include "DecisionWindow.h"

DecisionWindow::DecisionWindow(sf::Vector2f pos, std::string messege)
{
	sf::Vector2f backgroundSize = { 550, 200 }, yesRectSize = { 80, 50 }, noRectSize = { 80, 50 };
	backgroundRect.setSize(backgroundSize);
	backgroundRect.setOrigin(backgroundSize.x / 2, backgroundSize.y / 2);
	backgroundRect.setPosition(pos);
	backgroundRect.setFillColor(sf::Color(54, 56, 59));
	backgroundRect.setOutlineThickness(0.5);
	backgroundRect.setOutlineColor(sf::Color::Black);


	yesOptionRect.setSize(yesRectSize);
	yesOptionRect.setOrigin(yesRectSize.x / 2, yesRectSize.y / 2);
	yesOptionRect.setPosition(pos.x - 50, pos.y + 30);
	yesOptionRect.setFillColor(sf::Color(20, 20, 20));
	yesOptionRect.setOutlineThickness(2);
	yesOptionRect.setOutlineColor(sf::Color::Black);

	noOptionRect.setSize(noRectSize);
	noOptionRect.setOrigin(noRectSize.x / 2, noRectSize.y / 2);
	noOptionRect.setPosition(pos.x+50, pos.y + 30);
	noOptionRect.setFillColor(sf::Color(20,20,20));
	noOptionRect.setOutlineThickness(2);
	noOptionRect.setOutlineColor(sf::Color::Black);

	auto fontManager = FontManager::getInstance();
	messegeText.setFont(fontManager->getFont());
	messegeText.setCharacterSize(30);
	messegeText.setFillColor(sf::Color::White);
	messegeText.setString(messege);
	
	auto messegeTextRect = messegeText.getLocalBounds();
	messegeText.setOrigin(messegeTextRect.left + messegeTextRect.width / 2,
		messegeTextRect.top + messegeTextRect.height / 2);
	messegeText.setPosition({pos.x, pos.y-40});

	yesText.setFont(fontManager->getFont());
	yesText.setCharacterSize(24);
	yesText.setFillColor(sf::Color::White);
	yesText.setString("Yes");

	auto yesTextRect = yesText.getLocalBounds();
	yesText.setOrigin(yesTextRect.left + yesTextRect.width / 2,
		yesTextRect.top + yesTextRect.height / 2);
	yesText.setPosition(yesOptionRect.getPosition());

	noText.setFont(fontManager->getFont());
	noText.setCharacterSize(24);
	noText.setFillColor(sf::Color::White);
	noText.setString("No");

	auto noTextRect = noText.getLocalBounds();
	noText.setOrigin(noTextRect.left + noTextRect.width / 2,
		noTextRect.top + noTextRect.height / 2);
	noText.setPosition(noOptionRect.getPosition());
}

std::optional<bool> DecisionWindow::getDecision(sf::Vector2i mousePos)
{
	if (mousePos.x > yesOptionRect.getPosition().x - yesOptionRect.getSize().x / 2
		&& mousePos.x < yesOptionRect.getPosition().x + yesOptionRect.getSize().x / 2
		&& mousePos.y > yesOptionRect.getPosition().y - yesOptionRect.getSize().y / 2
		&& mousePos.y < yesOptionRect.getPosition().y + yesOptionRect.getSize().y / 2)
	{
		return { true };
	}
	else if (mousePos.x > noOptionRect.getPosition().x - noOptionRect.getSize().x / 2
		&& mousePos.x < noOptionRect.getPosition().x + noOptionRect.getSize().x / 2
		&& mousePos.y > noOptionRect.getPosition().y - noOptionRect.getSize().y / 2
		&& mousePos.y < noOptionRect.getPosition().y + noOptionRect.getSize().y / 2)
	{
		return { false };
	}
	else
		return {};
}
