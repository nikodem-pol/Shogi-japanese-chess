#include "DropSquare.h"

DropSquare::DropSquare(char figureSym, sf::Vector2f dropSquarePosition) : counter(0)
{
	this->figureCharSymbol = figureSym;
	square.setFillColor(sf::Color::White);
	square.setSize(squareSize);
	square.setOrigin(squareSize.x / 2, squareSize.y / 2);
	square.setPosition(dropSquarePosition);


	auto fontManager = FontManager::getInstance();

	figureSymbol.setFont(fontManager->getFont());
	figureSymbol.setCharacterSize(24);
	figureSymbol.setString(figureSym);
	figureSymbol.setFillColor(sf::Color::White);
	figureSymbol.setStyle(sf::Text::Bold);
	//Center text
	auto symbolfigureSymbolTextRect = figureSymbol.getLocalBounds();
	figureSymbol.setOrigin(symbolfigureSymbolTextRect.left + symbolfigureSymbolTextRect.width / 2,
		symbolfigureSymbolTextRect.top);
	figureSymbol.setPosition(square.getPosition().x, square.getPosition().y + square.getSize().y / 2 + spacing);


	availableFigureCounter.setFont(fontManager->getFont());
	availableFigureCounter.setCharacterSize(30);
	availableFigureCounter.setString(std::to_string(counter));
	availableFigureCounter.setFillColor(sf::Color::Black);
	availableFigureCounter.setStyle(sf::Text::Bold);
	//Center text
	auto availableFigureTextRect = availableFigureCounter.getLocalBounds();
	availableFigureCounter.setOrigin(availableFigureTextRect.left + availableFigureTextRect.width / 2,
		availableFigureTextRect.top + availableFigureTextRect.height / 2);
	availableFigureCounter.setPosition(square.getPosition());
}

void DropSquare::draw(sf::RenderTarget& target, sf::RenderStates state) const 
{
	target.draw(square, state);
	target.draw(figureSymbol, state);
	target.draw(availableFigureCounter, state);
}

DropSquare& DropSquare::operator=(DropSquare other) noexcept
{
	/*this->figureSymbol = other.figureSymbol;
	this->availableFigureCounter = other.availableFigureCounter;
	this->font = other.font;
	this->squareSize = other.squareSize;
	this->square = other.square;
	this->counter = other.counter;
	this->spacing = other.spacing;*/

	auto fontManager = FontManager::getInstance();

	std::swap(figureSymbol, other.figureSymbol);
	std::swap(availableFigureCounter, other.availableFigureCounter);
	availableFigureCounter.setFont(fontManager->getFont());
	figureSymbol.setFont(fontManager->getFont());
	std::swap(squareSize, other.squareSize);
	std::swap(square, other.square);
	std::swap(counter, other.counter);
	std::swap(spacing, other.spacing);


	return *this;
}


void DropSquare::incrementFigureCounter()
{
	if (this->counter == 0)
		square.setFillColor(sf::Color(41, 134, 204)); //Niebieski

	++counter;
	availableFigureCounter.setString(std::to_string(counter));

}

void DropSquare::decrementFigureCounter()
{
	if (this->counter == 1)
		square.setFillColor(sf::Color::White);

	--counter;
	availableFigureCounter.setString(std::to_string(counter));
}

void DropSquare::highligth()
{
	this->square.setFillColor(sf::Color::Red);
}

void DropSquare::restoreColor()
{
	if (this->counter > 0)
		square.setFillColor(sf::Color(41, 134, 204)); //Niebieski
	else
		square.setFillColor(sf::Color::White);
}
