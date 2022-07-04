#include "PawnMovesCalculator.h"

std::set<std::pair<int, int>> PawnMovesCalculator::getMoves(sf::Vector2i squareIndex)
{
	std::set<std::pair<int, int>> setOfPotentialMoves;
	if (pawnTeam == team::White && ++squareIndex.y <= 8)
	{
		auto potentialMove = std::make_pair(squareIndex.x, squareIndex.y);
		setOfPotentialMoves.insert(potentialMove);
		return setOfPotentialMoves;
	}

	if (pawnTeam == team::Black && --squareIndex.y >= 0)
	{
		auto potentialMove = std::make_pair(squareIndex.x, squareIndex.y);
		setOfPotentialMoves.insert(potentialMove);
		return setOfPotentialMoves;
	}

	return setOfPotentialMoves;
}