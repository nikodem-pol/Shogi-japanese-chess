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
	Square(sf::Vector2f size, sf::Vector2f pos) : highlighted(false)
	{
		shape.setPosition(pos);
		shape.setSize(size);
		shape.setOrigin(size.x / 2, size.y / 2);
		shape.setFillColor(sqColor);
		figure.reset(nullptr);
	}

	Square(sf::Vector2f size, sf::Vector2f pos, std::unique_ptr<Figure> fig) : Square(size, pos)
	{
		figure = std::move(fig);
	}

	Square(Square&& other) noexcept
	{
		shape = std::move(other.shape);
		sqColor = std::move(other.sqColor);
		figure = std::move(other.figure);
		highlighted = std::move(other.highlighted);
		//std::cout << "Moved\n";
	}

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override
	{
		target.draw(shape, state);
		if (figure != nullptr)
		{
			target.draw(*figure, state);
		}
	}

	Square& operator=(Square&& other) noexcept
	{
		shape = std::move(other.shape);
		sqColor = std::move(other.sqColor);
		figure = std::move(other.figure);
		highlighted = std::move(other.highlighted);
		return *this;
	}

	/*
	* Zmiana koloru pola
	*/
	void changeColor(sf::Color color) 
	{
		shape.setFillColor(color);
	}


	/*
	*	Przemieszczanie figury na wolne pole
	*/
	void giveFigure(Square& chosenSq) 
	{
		//
		chosenSq.figure = std::move(this->figure);
		chosenSq.figure->changePos(chosenSq.getPos());
		//
	}

	/*
	*	Bicie figure z pola chosenSq
	*/
	void takes(Square& chosenSq)  
	{
		std::unique_ptr<Figure> figureToDelete = nullptr;
		//wymiana figurami
		figure.swap(chosenSq.figure);

		//Czyszczenie pola
		figure.swap(figureToDelete);

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

	std::optional<figureType> getFigureType()
	{
		if (figure != nullptr)
		{
			std::optional<figureType> typeOfHeldFigure = figure->getFigureType();
			return typeOfHeldFigure;
		}
		else
			return {};
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

