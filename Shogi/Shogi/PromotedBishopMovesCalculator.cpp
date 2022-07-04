#include "PromotedBishopMovesCalculator.h"

std::set<std::pair<int, int>> PromotedBishopMovesCalculator::getMoves(sf::Vector2i squareIndex)
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

	//////
	xIndex = squareIndex.x;
	yIndex = squareIndex.y;

	if (yIndex + 1 <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex + 1));
	}

	if (yIndex - 1 >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex - 1));
	}

	if (xIndex + 1 <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex + 1, yIndex));
	}

	if (xIndex - 1 >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex - 1, yIndex));
	}

	return setOfPotentialMoves;
}