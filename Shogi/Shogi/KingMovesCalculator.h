#pragma once
#include "MovesCalculationFunction.h"
#include "Figure.h"

class KingMovesCalculator : public MovesCalculationFunction
{
	team kingTeam;
public:
	KingMovesCalculator(team kTeam) : kingTeam(kTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::King; }
	team getTeam() { return kingTeam; };

};

