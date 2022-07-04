#pragma once
#include "MovesCalculationFunction.h"

class RookMovesCalculator : public MovesCalculationFunction
{
	team rookTeam;
public:
	RookMovesCalculator(team rTeam) : rookTeam(rTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Rook; }
	team getTeam() { return rookTeam; };

};

