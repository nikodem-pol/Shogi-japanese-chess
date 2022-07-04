#pragma once
#include "MovesCalculationFunction.h"
#include "Figure.h"

class SilverMovesCalculator : public MovesCalculationFunction
{
	team silverTeam;
public:
	SilverMovesCalculator(team sTeam) : silverTeam(sTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Silver; }
	team getTeam() { return silverTeam; };

};

