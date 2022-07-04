#pragma once
#include "MovesCalculationFunction.h"

class PromotedRookMovesCalculator : public MovesCalculationFunction
{
	team rookTeam;
public:
	PromotedRookMovesCalculator(team rTeam) : rookTeam(rTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Rook; }
	team getTeam() { return rookTeam; };

};

