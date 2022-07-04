#include "PromotedRookMovesCalculator.h"

std::set<std::pair<int, int>> PromotedRookMovesCalculator::getMoves(sf::Vector2i squareIndex)
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
	//////////////////////////////////
	xIndex = squareIndex.x;
	yIndex = squareIndex.y;

	if (xIndex + 1 <= 8 && yIndex + 1 <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex + 1, yIndex + 1));
	}

	if (xIndex + 1 <= 8 && yIndex - 1 >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex + 1, yIndex - 1));

	}

	if (xIndex - 1 >= 0 && yIndex - 1 >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex - 1, yIndex - 1));
	}

	if (xIndex - 1 >= 0 && yIndex + 1 <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex - 1, yIndex + 1));
	}

	return setOfPotentialMoves;
}