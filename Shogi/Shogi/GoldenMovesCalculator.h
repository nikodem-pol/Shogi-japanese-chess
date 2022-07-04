#pragma once
#include "MovesCalculationFunction.h"
#include "Figure.h"

class GoldenMovesCalculator : public MovesCalculationFunction
{
	team goldenTeam;
public:
	GoldenMovesCalculator(team gTeam) : goldenTeam(gTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Golden; }
	team getTeam() { return goldenTeam; };

};

