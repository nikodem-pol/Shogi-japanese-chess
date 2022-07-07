#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include "Figure.h"

class Square : public sf::Drawable
{
	sf::Color sqColor = sf::Color::White, highlightColor = sf::Color::Red;
	sf::RectangleShape shape;
	std::unique_ptr<Figure> figure;
	bool highlighted;

public:
	Square() = default;
	Square(sf::Vector2f size, sf::Vector2f pos);
	Square(sf::Vector2f size, sf::Vector2f pos, std::unique_ptr<Figure> fig) : Square(size, pos)
	{
		figure = std::move(fig);
	}
	Square(Square&& other) noexcept;
	Square& operator=(Square&& other) noexcept;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void giveFigure(Square& chosenSq);
	void takes(Square& chosenSq);
	std::optional<figureType> getFigureType();

	/*
	* Zmiana koloru pola
	*/
	void changeColor(sf::Color color) 
	{
		shape.setFillColor(color);
	}

	void setFigure(std::unique_ptr<Figure>& droppedFigure)
	{
		this->figure = std::move(droppedFigure);
		figure->changePos(this->getPos());
	}

	sf::Vector2f getPos()
	{
		return shape.getPosition();
	}

	void highlight()
	{
		highlighted = true;
		shape.setFillColor(highlightColor);
	}

	void restoreColor()
	{
		highlighted = false;
		shape.setFillColor(sqColor);
	}

	bool isHighlighted()
	{
		return highlighted;
	}

	bool isOccupied()
	{
		if (figure != nullptr)
			return true;
		else
			return false;
	}

	team getTeam()
	{
		if (figure != nullptr)
			return figure->getTeam();
		else
			return team::Empty;
	}

	void promoteFigure()
	{
		if (figure != nullptr)
		{
			figure->promote();
		}
	}

	bool isPromoted()
	{
		if (figure != nullptr)
			return figure->isPromoted();
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalcFunc()
	{
		return figure->getMovesCalculationFunc();
	}
};

