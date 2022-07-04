#include "MovesCalculationFunction.h"
#include "Figure.h"

class PawnMovesCalculator : public MovesCalculationFunction
{
	team pawnTeam;
public:
	PawnMovesCalculator(team pTeam) : pawnTeam(pTeam) {}
	std::set<std::pair<int, int>> getMoves(sf::Vector2i squareIndex) override;
	figureType getType() override { return figureType::Pawn; }
	team getTeam() { return pawnTeam; };
};
