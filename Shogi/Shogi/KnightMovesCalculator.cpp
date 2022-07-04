#include "KnightMovesCalculator.h"

std::set<std::pair<int, int>> KnightMovesCalculator::getMoves(sf::Vector2i squareIndex)
{
	std::set<std::pair<int, int>> setOfPotentialMoves;

	int xIndex = squareIndex.x;
	int yIndex = squareIndex.y;

	if (knightTeam == team::White && yIndex + 2 <= 8)
	{
		if (xIndex + 1 <= 8)
			setOfPotentialMoves.insert(std::make_pair(xIndex + 1, yIndex + 2));

		if(xIndex - 1 >= 0)
			setOfPotentialMoves.insert(std::make_pair(xIndex - 1, yIndex + 2));

		return setOfPotentialMoves;
	}

	if (knightTeam == team::Black && yIndex - 2 >= 0)
	{
		if (xIndex + 1 <= 8)
			setOfPotentialMoves.insert(std::make_pair(xIndex + 1, yIndex - 2));

		if (xIndex - 1 >= 0)
			setOfPotentialMoves.insert(std::make_pair(xIndex - 1, yIndex - 2));

		return setOfPotentialMoves;
	}

	return setOfPotentialMoves;
}
