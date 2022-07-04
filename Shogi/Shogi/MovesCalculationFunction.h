#pragma once
#include <set>
#include <utility>
#include "Enums.h"
#include "SFML/Graphics.hpp"

class MovesCalculationFunction
{
public:
	virtual std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) = 0;
	virtual figureType getType() = 0;
	virtual team getTeam() = 0;
};

