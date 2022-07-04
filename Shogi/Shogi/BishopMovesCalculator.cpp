#include "BishopMovesCalculator.h"

std::set<std::pair<int, int>> BishopMovesCalculator::getMoves(sf::Vector2i squareIndex)
{
	std::set<std::pair<int, int>> setOfPotentialMoves;
	int xIndex = squareIndex.x;
	int yIndex = squareIndex.y;

	while (++xIndex <= 8 && ++yIndex <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex));
	}

	xIndex = squareIndex.x;
	yIndex = squareIndex.y;

	while (++xIndex <= 8 && --yIndex >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex));
	}

	xIndex = squareIndex.x;
	yIndex = squareIndex.y;

	while (--xIndex >= 0 && --yIndex >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex));
	}

	xIndex = squareIndex.x;
	yIndex = squareIndex.y;

	while (--xIndex >= 0 && ++yIndex <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex));
	}

	return setOfPotentialMoves;
}
