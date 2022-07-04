#include "RookMovesCalculator.h"

std::set<std::pair<int, int>> RookMovesCalculator::getMoves(sf::Vector2i squareIndex)
{
	std::set<std::pair<int, int>> setOfPotentialMoves;

	int yIndex = squareIndex.y;
	while (++yIndex <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(squareIndex.x, yIndex));
	}

	yIndex = squareIndex.y;
	while (--yIndex >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(squareIndex.x, yIndex));
	}

	int xIndex = squareIndex.x;
	while (++xIndex <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, squareIndex.y));
	}

	xIndex = squareIndex.x;
	while (--xIndex >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, squareIndex.y));
	}

	return setOfPotentialMoves;
}

