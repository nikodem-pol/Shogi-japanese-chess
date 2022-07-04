#include "MovesCalculationFunction.h"
#include "Figure.h"

class KnightMovesCalculator : public MovesCalculationFunction
{
	team knightTeam;
public:
	KnightMovesCalculator(team nTeam) : knightTeam(nTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Knight; }
	team getTeam() { return knightTeam; };

};