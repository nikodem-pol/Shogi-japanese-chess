#include "SilverMovesCalculator.h"

std::set<std::pair<int, int>> SilverMovesCalculator::getMoves(sf::Vector2i squareIndex)
{
	std::set<std::pair<int, int>> setOfPotentialMoves;
	int xIndex = squareIndex.x;
	int yIndex = squareIndex.y;

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

	if (silverTeam == team::White && yIndex + 1 <= 8)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex + 1));
	}		

	if (silverTeam == team::Black && yIndex - 1 >= 0)
	{
		setOfPotentialMoves.insert(std::make_pair(xIndex, yIndex - 1));
	}
	return setOfPotentialMoves;
}
