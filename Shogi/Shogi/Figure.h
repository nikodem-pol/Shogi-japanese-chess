#pragma once
#include "MovesCalculationFunction.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>


class Figure : public sf::Drawable
{
protected:
	team figureTeam;
	sf::Sprite figure;
	sf::Vector2f figDimensions = { 80,80 };
	std::shared_ptr<MovesCalculationFunction> movesCalcFunction;
	bool promoted = false;
public:
	Figure() = default;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override
	{
		target.draw(figure, state);
	}

	virtual figureType getFigureType() = 0;

	virtual void promote() = 0;

	void changePos(sf::Vector2f pos)
	{
		figure.setPosition(pos);
	}

	///Poprawiæ
	virtual std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const = 0;

	team getTeam()
	{
		return figureTeam;
	}

	bool isPromoted()
	{
		return promoted;
	}
};

