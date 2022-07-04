#pragma once
#include <string>
#include "FontManager.h"
#include "SFML/Graphics.hpp"

class DropSquare : public sf::Drawable
{
	sf::Text figureSymbol;
	char figureCharSymbol;
	sf::Text availableFigureCounter;
	sf::Vector2f squareSize = { 40.0,40.0 };
	sf::RectangleShape square;
	int counter;
	float spacing = 4.f;
public:
	DropSquare() = default;
	DropSquare(char figureSym, sf::Vector2f dropSquarePosition);
	DropSquare(DropSquare&& other) noexcept
	{
		auto fontManager = FontManager::getInstance();

		this->figureSymbol = std::move(other.figureSymbol);
		this->availableFigureCounter = std::move(other.availableFigureCounter);
		this->squareSize = std::move(other.squareSize);
		this->figureCharSymbol = std::move(other.figureCharSymbol);
		this->availableFigureCounter.setFont(fontManager->getFont());
		this->figureSymbol.setFont(fontManager->getFont());
		this->square = std::move(other.square);
		this->counter = std::move(other.counter);
		this->spacing = std::move(other.spacing);

	}
	~DropSquare() = default;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	DropSquare& operator=(DropSquare other) noexcept;
	void highligth();
	void restoreColor();
	void incrementFigureCounter();
	void decrementFigureCounter();
	bool isAvailableToDrop()
	{
		if (this->counter > 0) 
			return true;
		else
			return false;
	}
	int getFigureCounter() { return counter; }
	char getFigureSymbol()
	{
		return figureCharSymbol;
	}
	sf::Vector2f getPosition()
	{
		return square.getPosition();
	}
	sf::Vector2f getSquareSize()
	{
		return squareSize;
	}

};

