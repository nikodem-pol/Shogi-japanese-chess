#include "LanceMovesCalculator.h"

std::set<std::pair<int, int>> LanceMovesCalculator::getMoves(sf::Vector2i squareIndex)
{
	std::set<std::pair<int, int>> setOfPotentialMoves;

	int yIndex = squareIndex.y;

	if (lanceTeam == team::White)
	{
		while (++yIndex <= 8)
		{
			setOfPotentialMoves.insert(std::make_pair(squareIndex.x, yIndex));
		}
	}

	if (lanceTeam == team::Black)
	{
		while (--yIndex >= 0)
		{
			setOfPotentialMoves.insert(std::make_pair(squareIndex.x, yIndex));
		}
	}

	return setOfPotentialMoves;
}
