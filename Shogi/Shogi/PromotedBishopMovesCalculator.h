#pragma once
#include "MovesCalculationFunction.h"

class PromotedBishopMovesCalculator : public MovesCalculationFunction
{
	team bishopTeam;
public:
	PromotedBishopMovesCalculator(team bTeam) : bishopTeam(bTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Bishop; }
	team getTeam() { return bishopTeam; };
};

