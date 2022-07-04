#pragma once
#include "MovesCalculationFunction.h"
#include "Figure.h"

class LanceMovesCalculator : public MovesCalculationFunction
{
	team lanceTeam;
public:
	LanceMovesCalculator(team lTeam) : lanceTeam(lTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Lance; }
	team getTeam() { return lanceTeam; };

};

