#include "GameLogic.h"
team reverseTeam(team t)
{
	if (t == team::Black)
		return team::White;
	else
		return team::Black;
}

std::set<std::pair<int, int>> findFiguresOfType(figureType type, team t, Board& board)
{
	std::set<std::pair<int, int>> figures;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j].getFigureType() == type && board[i][j].getTeam() == t)
				figures.insert({ i,j });
		}
	}

	return figures;
}

std::set<std::pair<int, int>> GameLogic::calculateMoves(sf::Vector2i Index)
{
	auto movesCalcFunc = board.getMovesCalcFunc(Index);

	switch (movesCalcFunc->getType())
	{
	case figureType::Bishop:
		return calculateBishopAndRookMoves(Index, movesCalcFunc);
		break;

	case figureType::Rook:
		return calculateBishopAndRookMoves(Index, movesCalcFunc);
		break;

	case figureType::King:
		return calculateKingMoves(Index, movesCalcFunc);
		break;

	case figureType::Lance:
		return calculateLanceMoves(Index, movesCalcFunc);
		break;

	default:
		return movesCalcFunc->getMoves(Index);
		break;
	}
}

void GameLogic::highlightCorrectMoves(sf::Vector2i index)
{
	auto movesCalcFunc = board.getMovesCalcFunc(index);
	auto moves = calculateMoves(index);
	if (!(movesCalcFunc->getType() == figureType::King))
	{
		filterBlockingCheckMoves(moves, movesCalcFunc->getTeam());
		calculatePinnedFigureMoves(index, moves, movesCalcFunc->getTeam());
	}
	board.highligth(moves, movesCalcFunc->getTeam());
}

std::set<std::pair<int, int>> GameLogic::calculateBishopAndRookMoves(sf::Vector2i index, std::shared_ptr<MovesCalculationFunction> calcFunc)
{
	auto moves = calcFunc->getMoves(index);
	std::set<std::pair<int, int>> correctMoves;

	correctMoves.merge(checkUpperRightMoves(index, moves));
	correctMoves.merge(checkLowerRightMoves(index, moves));
	correctMoves.merge(checkUpperLeftMoves(index, moves));
	correctMoves.merge(checkLowerLeftMoves(index, moves));
	correctMoves.merge(checkUpMoves(index, moves));
	correctMoves.merge(checkDownMoves(index, moves));
	correctMoves.merge(checkLeftMoves(index, moves));
	correctMoves.merge(checkRightMoves(index, moves));

	return correctMoves;
}

std::set<std::pair<int, int>> GameLogic::calculateLanceMoves(sf::Vector2i index, std::shared_ptr<MovesCalculationFunction> calcFunc)
{
	auto moves = calcFunc->getMoves(index);
	if (calcFunc->getTeam() == team::White)
	{
		return checkUpMoves(index, moves);
	}
	else
	{
		return checkDownMoves(index, moves);
	}
}

std::set<std::pair<int, int>> GameLogic::calculateKingMoves(sf::Vector2i index, std::shared_ptr<MovesCalculationFunction> calcFunc)
{
	auto potentialMoves = calcFunc->getMoves(index);
	std::set<std::pair<int, int>> correctMoves;
	if (calcFunc->getTeam() == team::Black)
	{
		std::ranges::for_each(potentialMoves, [this, &potentialMoves, &correctMoves](std::pair<int, int> move)
			{
				if (!whitesControledSquares.contains(move))
				{
					correctMoves.insert(move);
				}
			});

		std::set<std::pair<int, int>> movesToDrop;
		std::ranges::for_each(whitesCheckingFigures, [this, &correctMoves, &movesToDrop](auto figure)
			{
				auto type = board[figure.first][figure.second].getFigureType().value();
				auto kingPos = board.getKingPos(team::Black);
				if (type == figureType::Rook || type == figureType::Lance)
				{
					if (kingPos.first == figure.first )
					{
						for (auto move : correctMoves)
						{
							if (move!= figure && move.first == figure.first)
								movesToDrop.insert(move);
						}
					}
					else if ( kingPos.second == figure.second && type != figureType::Lance)
					{
						for (auto move : correctMoves)
						{
							if (move != figure && move.second == figure.second)
								movesToDrop.insert(move);
						}
					}
				}
				else if (type == figureType::Bishop)
				{
					double dy_dx = (double)(figure.first - kingPos.first) / (double)(figure.second - kingPos.second);
					for (auto& move : correctMoves)
					{
						double dy = figure.second - move.second;
						if (dy != 0 && dy_dx == (double)(figure.first - move.first) / dy)
						{
							movesToDrop.insert(move);
						}
					}
				}
			});

		std::set<std::pair<int, int>> correctMoves2;
		for (auto move : correctMoves)
		{
			if (!movesToDrop.contains(move))
			{
				correctMoves2.insert(move);
			}
		}
		return correctMoves2;
	}
	else
	{
		std::ranges::for_each(potentialMoves, [this, &potentialMoves, &correctMoves](std::pair<int, int> move)
			{
				if (!blacksControledSquares.contains(move))
				{
					correctMoves.insert(move);
				}
			});

		std::set<std::pair<int, int>> movesToDrop;
		std::ranges::for_each(blacksCheckingFigures, [this, &correctMoves, &movesToDrop](auto figure)
			{
				auto type = board[figure.first][figure.second].getFigureType().value();
				auto kingPos = board.getKingPos(team::White);
				if (type == figureType::Rook || type == figureType::Lance)
				{
					if (kingPos.first == figure.first)
					{
						for (auto& move : correctMoves)
						{
							if (move != figure && move.first == figure.first)
								movesToDrop.insert(move);
						}
					}
					else if (kingPos.second == figure.second && type != figureType::Lance)
					{
						for (auto& move : correctMoves)
						{
							if (move != figure && move.second == figure.second)
								movesToDrop.insert(move);
						}
					}
				}
				else if (type == figureType::Bishop)
				{
					double dy_dx = (double)(figure.first - kingPos.first) / (double)(figure.second - kingPos.second);
					for (auto& move : correctMoves)
					{
						double dx = figure.second - move.second;
						if (dx != 0 && dy_dx == (double)(figure.first - move.first) / dx)
						{
							movesToDrop.insert(move);
						}
					}
				}
			});

		std::set<std::pair<int, int>> correctMoves2;
		for (auto move : correctMoves)
		{
			if (!movesToDrop.contains(move))
			{
				correctMoves2.insert(move);
			}
		}
		return correctMoves2;
	}

	
}

//Utility
std::set<std::pair<int, int>> GameLogic::checkUpMoves(sf::Vector2i index, std::set<std::pair<int,int>> moves)
{
	auto isUp = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.first == index.x && currentSq.second - index.y > 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto upMoves = std::views::filter(moves, isUp);

	if (upMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(upMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(upMoves.begin(), upMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistance = nearestSq.second - index.y;
				int distance = abs(sq.second - index.y);

				if (distance < currentMinDistance)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return sqIn.second - index.y <= nearestSq.second - index.y;
			};

			auto correctMoves = std::views::filter(upMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}
	}
}

std::set<std::pair<int, int>> GameLogic::checkDownMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto isDown = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.first == index.x && currentSq.second - index.y < 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto downMoves = std::views::filter(moves, isDown);

	if (downMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(downMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(downMoves.begin(), downMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistance = abs(nearestSq.second - index.y);
				int distance = abs(sq.second - index.y);

				if (distance < currentMinDistance)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs(sqIn.second - index.y) <= abs(nearestSq.second - index.y);
			};

			auto correctMoves = std::views::filter(downMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}
	}
}

std::set<std::pair<int, int>> GameLogic::checkRightMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto isRight = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.second == index.y && currentSq.first - index.x < 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto rightMoves = std::views::filter(moves, isRight);

	if (rightMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(rightMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(rightMoves.begin(), rightMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistance = abs(nearestSq.first - index.x);
				int distance = abs(sq.first - index.x);

				if (distance < currentMinDistance)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs(sqIn.first - index.x) <= abs(nearestSq.first - index.x);
			};

			auto correctMoves = std::views::filter(rightMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}

	}
}

std::set<std::pair<int, int>> GameLogic::checkLeftMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto isLeft = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.second == index.y && currentSq.first - index.x > 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto leftMoves = std::views::filter(moves, isLeft);

	if (leftMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(leftMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(leftMoves.begin(), leftMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistance = abs(nearestSq.first - index.x);
				int distance = abs(sq.first - index.x);

				if (distance < currentMinDistance)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs(sqIn.first - index.x) <= abs(nearestSq.first - index.x);
			};

			auto correctMoves = std::views::filter(leftMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}

	}
}

std::set<std::pair<int, int>> GameLogic::checkUpperRightMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto upperRight = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.first - index.x > 0 && currentSq.second - index.y > 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto upperRightMoves = std::views::filter(moves, upperRight);

	if (upperRightMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(upperRightMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(upperRightMoves.begin(), upperRightMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistanceSquare = abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
				int distanceSquare = abs((sq.first - index.x) * (sq.second - index.y));

				if (distanceSquare < currentMinDistanceSquare)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs((sqIn.first - index.x) * (sqIn.second - index.y)) <= abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
			};

			auto correctMoves = std::views::filter(upperRightMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}

	}
}

std::set<std::pair<int, int>> GameLogic::checkUpperLeftMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto upperLeft = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.first - index.x < 0 && currentSq.second - index.y > 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto upperLeftMoves = std::views::filter(moves, upperLeft);

	if (upperLeftMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(upperLeftMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(upperLeftMoves.begin(), upperLeftMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistanceSquare = abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
				int distanceSquare = abs((sq.first - index.x) * (sq.second - index.y));

				if (distanceSquare < currentMinDistanceSquare)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs((sqIn.first - index.x) * (sqIn.second - index.y)) <= abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
			};

			auto correctMoves = std::views::filter(upperLeftMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}

	}
}

std::set<std::pair<int, int>> GameLogic::checkLowerLeftMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto lowerLeft = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.first - index.x < 0 && currentSq.second - index.y < 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto lowerLeftMoves = std::views::filter(moves, lowerLeft);

	if (lowerLeftMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(lowerLeftMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(lowerLeftMoves.begin(), lowerLeftMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistanceSquare = abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
				int distanceSquare = abs((sq.first - index.x) * (sq.second - index.y));

				if (distanceSquare < currentMinDistanceSquare)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs((sqIn.first - index.x) * (sqIn.second - index.y)) <= abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
			};

			auto correctMoves = std::views::filter(lowerLeftMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}

	}
}

std::set<std::pair<int, int>> GameLogic::checkLowerRightMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves)
{
	auto lowerRight = [this, index](std::pair<int, int> currentSq)
	{
		return currentSq.first - index.x > 0 && currentSq.second - index.y < 0;
	};

	auto occupied = [this](std::pair<int, int> index)
	{
		return board.isOccupied({ index.first, index.second });
	};

	auto lowerRightMoves = std::views::filter(moves, lowerRight);

	if (lowerRightMoves.empty())
	{
		return std::set<std::pair<int, int>>();
	}
	else
	{
		auto occupiedSquares = std::views::filter(lowerRightMoves, occupied);

		if (occupiedSquares.empty())
		{
			return std::set<std::pair<int, int>>(lowerRightMoves.begin(), lowerRightMoves.end());
		}
		else
		{
			auto nearestSq = occupiedSquares.front();

			for (auto sq : occupiedSquares)
			{
				int currentMinDistanceSquare = abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
				int distanceSquare = abs((sq.first - index.x) * (sq.second - index.y));

				if (distanceSquare < currentMinDistanceSquare)
					nearestSq = sq;
			}

			auto filterCorrectMoves = [this, nearestSq, index](std::pair<int, int> sqIn)
			{
				return abs((sqIn.first - index.x) * (sqIn.second - index.y)) <= abs((nearestSq.first - index.x) * (nearestSq.second - index.y));
			};

			auto correctMoves = std::views::filter(lowerRightMoves, filterCorrectMoves);
			std::set<std::pair<int, int>> correctMovesSet(correctMoves.begin(), correctMoves.end());
			return correctMovesSet;
		}

	}
}

void GameLogic::calculateControledSquares(team t, bool selector)
{
	if (t == team::Black)
	{
		blacksCheckingFigures.clear();
	}
	else if (t == team::White)
	{
		whitesCheckingFigures.clear();
	}

	std::set<std::pair<int, int>> moves;
	std::vector<std::future<std::set<std::pair<int, int>>>> workers;

	auto func = std::bind(&GameLogic::calculate, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

	for (int i = 0; i < 9; ++i)
	{
		workers.push_back(std::async(std::launch::async, func, ref(board[i]), i, t, selector));
	}

	for (int i = 0; i < 9; ++i)
	{
		moves.merge(workers[i].get());
	}


	if (t == team::Black)
	{
		this->blacksControledSquares = moves;
	}
	else
	{
		this->whitesControledSquares = moves;
	}
}

std::mutex chackingFiguresMutex;

std::set<std::pair<int, int>> GameLogic::calculate(std::array<Square,9>& column, int rowNum, team t, bool selector)
{
	std::set<std::pair<int, int>> moves;
	for (int i = 0; i < 9; ++i)
	{
		if (column[i].isOccupied() && column[i].getTeam() == t)
		{
			if (column[i].getFigureType() == figureType::King && !selector)
			{
				moves.merge(column[i].getMovesCalcFunc()->getMoves({ rowNum, i }));
			}
			else
			{
				auto moreMoves = calculateMoves({ rowNum, i });
				auto moreMovesCopy = moreMoves;
				moves.merge(moreMoves);
				if (t == team::Black)
				{
					if (moreMovesCopy.contains(board.getKingPos(team::White)))
					{
						std::lock_guard<std::mutex> guard(chackingFiguresMutex);
						blacksCheckingFigures.insert({ rowNum, i });
					}
				}
				else
				{
					if (moreMovesCopy.contains(board.getKingPos(team::Black)))
					{
						std::lock_guard<std::mutex> guard(chackingFiguresMutex);
						whitesCheckingFigures.insert({ rowNum, i });
					}
				}
			}
		}
		if (selector && column[i].isOccupied() && column[i].getFigureType() != figureType::King )
		{
			filterBlockingCheckMoves(moves, t);
			calculatePinnedFigureMoves({ rowNum,i }, moves, t);
		}
		if (selector && column[i].isOccupied() && column[i].getFigureType() == figureType::King)
		{
			moves.merge(calculateKingMoves({ rowNum, i }, column[i].getMovesCalcFunc()));
		}
	}
	
	return moves;
}

void GameLogic::filterBlockingCheckMoves(std::set<std::pair<int, int>>& moves, team t)
{
	std::vector<std::pair<int,int>> movesCopy;

	if (t == team::White)
	{
		if (blacksCheckingFigures.empty())
			return;
		else
		{
			std::ranges::for_each(blacksCheckingFigures, [this, &movesCopy ,moves, t](std::pair<int,int> figure) 
				{
					auto type = board[figure.first][figure.second].getFigureType().value();
					auto kingPos = board.getKingPos(t);
					double dy_dx = (double)(figure.first - kingPos.first) / (double)(figure.second - kingPos.second);
					for (auto move : moves)
					{
						if (move == figure)
						{
							movesCopy.push_back(move);
						}
						else if (type == figureType::Rook || type == figureType::Lance)
						{
							if (move.first == figure.first
								&& (move.second > kingPos.second && move.second < figure.second || move.second < kingPos.second && move.second > figure.second))
								movesCopy.push_back(move);

							else if (move.second == figure.second
								&& (move.first > kingPos.first && move.first < figure.first || move.first < kingPos.first && move.first > figure.first)
								&& type != figureType::Lance)
								movesCopy.push_back(move);

						}
						else if (type == figureType::Bishop)
						{
							double dx = figure.second - move.second;
							int difX = figure.first - move.first;
							int difY = figure.second - move.second;

							if (dx != 0 && dy_dx == (double)(figure.first - move.first) / dx )
							{
								if (difX > 0 && move.first > kingPos.first && difY > 0 && move.second > kingPos.second
									|| difX > 0 && move.first > kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first && difY > 0 && move.second > kingPos.second)
									movesCopy.push_back(move);
							}
							///////////////////////////////
						}
					}
				});

			//Radzenie sobie z podwójnymi szachami
			std::ranges::for_each(blacksCheckingFigures, [this, &movesCopy, moves, t](std::pair<int, int> figure)
				{
					auto type = board[figure.first][figure.second].getFigureType().value();
					auto kingPos = board.getKingPos(t);
					double dy_dx = (double)(figure.first - kingPos.first) / (double)(figure.second - kingPos.second);
					if (type == figureType::Rook || type == figureType::Lance)
					{

						std::erase_if(movesCopy, [kingPos, figure](auto copiedMove)
							{
								return ((copiedMove.first != figure.first && (kingPos.second < figure.second || kingPos.second >  figure.second) && kingPos.first == figure.first)
									|| ((copiedMove.second != figure.second && (kingPos.first < figure.first || kingPos.first>  figure.first) && kingPos.second == figure.second)));
							});
					}
					else if (type == figureType::Bishop)
					{
						double dx = figure.second - kingPos.second;
						int difX = figure.first - kingPos.first;
						int difY = figure.second - kingPos.second;

						std::erase_if(movesCopy, [difX, difY, kingPos](auto move)
							{
								return !(difX > 0 && move.first > kingPos.first && difY > 0 && move.second > kingPos.second
									|| difX > 0 && move.first > kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first && difY > 0 && move.second > kingPos.second);
							});
					}
				});

		}
		moves = std::set<std::pair<int, int>>(movesCopy.begin(), movesCopy.end());
		return;
	}

	else if (t == team::Black)
	{
		if (whitesCheckingFigures.empty())
			return;
		else
		{
			std::ranges::for_each(whitesCheckingFigures, [this, &movesCopy, moves, t](std::pair<int, int> figure)
				{
					auto type = board[figure.first][figure.second].getFigureType().value();
					auto kingPos = board.getKingPos(t);
					double dy_dx = (double)(figure.first - kingPos.first) / (double)(figure.second - kingPos.second);
					for (auto move : moves)
					{
						if (move == figure)
						{
							movesCopy.push_back(move);
						}
						else if (type == figureType::Rook || type == figureType::Lance)
						{
							if (move.first == figure.first
								&& (move.second > kingPos.second && move.second < figure.second || move.second < kingPos.second && move.second > figure.second))
								movesCopy.push_back(move);

							else if (move.second == figure.second
								&& (move.first > kingPos.first && move.first < figure.first || move.first < kingPos.first && move.first > figure.first)
								&& type != figureType::Lance)
								movesCopy.push_back(move);

							std::erase_if(movesCopy, [kingPos, move, figure](auto copiedMove)
								{
									return (copiedMove.first != figure.first) || (copiedMove.second != figure.second);
								});
						}
						else if (type == figureType::Bishop)
						{
							double dx = figure.second - move.second;
							int difX = figure.first - move.first;
							int difY = figure.second - move.second;

							if (dx != 0 && dy_dx == (double)(figure.first - move.first) / dx)
							{
								if (difX > 0 && move.first > kingPos.first && difY > 0 && move.second > kingPos.second
									|| difX > 0 && move.first > kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first && difY > 0 && move.second > kingPos.second)
									movesCopy.push_back(move);
							}
							///////////////////
		
						}
					}
				});

			//Radzenie sobie z podwójnymi szachami
			std::ranges::for_each(whitesCheckingFigures, [this, &movesCopy, moves, t](std::pair<int, int> figure)
				{
					auto type = board[figure.first][figure.second].getFigureType().value();
					auto kingPos = board.getKingPos(t);
					double dy_dx = (double)(figure.first - kingPos.first) / (double)(figure.second - kingPos.second);
					if (type == figureType::Rook || type == figureType::Lance)
					{

						std::erase_if(movesCopy, [kingPos, figure](auto copiedMove)
							{
								return ((copiedMove.first != figure.first && (kingPos.second < figure.second || kingPos.second >  figure.second) && kingPos.first == figure.first)
									|| ((copiedMove.second != figure.second && (kingPos.first < figure.first || kingPos.first>  figure.first) && kingPos.second == figure.second)));
							});
					}
					else if (type == figureType::Bishop)
					{
						double dx = figure.second - kingPos.second;
						int difX = figure.first - kingPos.first;
						int difY = figure.second - kingPos.second;

						std::erase_if(movesCopy, [difX, difY, kingPos](auto move)
							{
								return !(difX > 0 && move.first > kingPos.first && difY > 0 && move.second > kingPos.second
									|| difX > 0 && move.first > kingPos.first && difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first&& difY < 0 && move.second < kingPos.second
									|| difX < 0 && move.first < kingPos.first&& difY > 0 && move.second > kingPos.second);
							});
					}
				});
		}
		moves = std::set<std::pair<int, int>>(movesCopy.begin(), movesCopy.end());
		return;
	}
}

void GameLogic::calculatePinnedFigureMoves(sf::Vector2i index, std::set<std::pair<int, int>>& moves, team t)
{
	std::vector<std::pair<int, int>> movesCopy(moves.begin(), moves.end());
	auto kingPos = board.getKingPos(t);
	if (index.x == kingPos.first || index.y == kingPos.second)
	{
		auto opponentsRooksAndLances = findFiguresOfType(figureType::Rook, reverseTeam(t), this->board);
		opponentsRooksAndLances.merge(findFiguresOfType(figureType::Lance, reverseTeam(t), this->board));
		std::ranges::for_each(opponentsRooksAndLances, [this, &movesCopy, index, kingPos](auto figure)
			{
				if (index.x == kingPos.first && kingPos.first == figure.first)
				{
					auto type = board[figure.first][figure.second].getFigureType().value();
					auto figureTeam = board[figure.first][figure.second].getTeam();
					//figura miêdzy królem a wie¿¹ przypadek 1: King->Figure->Rook
					if (kingPos.second - index.y < 0 && kingPos.second - figure.second < 0 && index.y - figure.second < 0
						&& (type == figureType::Rook || (type == figureType::Lance && figureTeam == team::Black)))
					{
						for (int i = kingPos.second + 1; i < figure.second; i++)
						{
							sf::Vector2i currentSq = { index.x, i };
							if (currentSq != index && board.isOccupied({ index.x, i }))
								return;
						}

						for (auto it = movesCopy.begin(); it < movesCopy.end();)
						{
							if (it->first != figure.first)
								it = movesCopy.erase(it);
							else
								++it;
						}
					}
					//figura miêdzy królem a wie¿¹ przypadek 2: Rook->Figure->King
					else if (kingPos.second - index.y > 0 && kingPos.second - figure.second > 0 && index.y - figure.second > 0
						&& (type == figureType::Rook || (type == figureType::Lance && figureTeam == team::White)))
					{
						for (int i = kingPos.second - 1; i > figure.second; i--)
						{
							sf::Vector2i currentSq = { index.x, i };
							if (currentSq != index && board.isOccupied({ index.x, i }))
								return;
						}

						for (auto it = movesCopy.begin(); it < movesCopy.end();)
						{
							if (it->first != figure.first)
								it = movesCopy.erase(it);
							else
								++it;
						}
					}
				}
				/////////////////////////////////////
				if (index.y == kingPos.second && kingPos.second == figure.second)
				{
					auto type = board[figure.first][figure.second].getFigureType().value();
					auto figureTeam = board[figure.first][figure.second].getTeam();
					//figura miêdzy królem a wie¿¹ przypadek 1: King->Figure->Rook
					if (kingPos.first - index.x < 0 && kingPos.first - figure.first < 0 && index.x - figure.first < 0
						&& type == figureType::Rook)
					{
						for (int i = kingPos.first + 1; i < figure.first; i++)
						{
							sf::Vector2i currentSq = { i, index.y };
							if (currentSq != index && board.isOccupied({ i, index.y }))
								return;
						}

						for (auto it = movesCopy.begin(); it < movesCopy.end();)
						{
							if (it->second != figure.second)
								it = movesCopy.erase(it);
							else
								++it;
						}
					}
					//figura miêdzy królem a wie¿¹ przypadek 2: Rook->Figure->King
					else if (kingPos.first - index.x > 0 && kingPos.first - figure.first > 0 && index.x - figure.first > 0
						&& type == figureType::Rook)
					{
						for (int i = kingPos.first - 1; i > figure.first; i--)
						{
							sf::Vector2i currentSq = { i, index.y };
							if (currentSq != index && board.isOccupied({ i, index.y }))
								return;
						}

						for (auto it = movesCopy.begin(); it < movesCopy.end();)
						{
							if (it->second != figure.second)
								it = movesCopy.erase(it);
							else
								++it;
						}
					}
				}
			});
	}

	if (abs(kingPos.first - index.x) == abs(kingPos.second - index.y))
	{
		auto opponentsBishops = findFiguresOfType(figureType::Bishop, reverseTeam(t), this->board);
		std::ranges::for_each(opponentsBishops, [this, &movesCopy, index, kingPos](auto bishop)
			{
				if (abs(kingPos.first - bishop.first) == abs(kingPos.second - bishop.second))
				{
					//Przypadek 1: King -> Figure -> Bishop - z prawej z góry
					if (kingPos.first - index.x < 0 && index.x - bishop.first < 0
						&& kingPos.second - index.y < 0 && index.y - bishop.second < 0)
					{
						sf::Vector2i tempIndex = { kingPos.first + 1, kingPos.second+1 };
						
						while (tempIndex.x < bishop.first && tempIndex.y < bishop.second)
						{
							if (board.isOccupied({ tempIndex.x, tempIndex.y }) && index != tempIndex)
								return;
							++tempIndex.x;
							++tempIndex.y;
						}
						std::erase_if(movesCopy, [tempIndex, bishop](auto move) {return abs(move.first - bishop.first) != abs(move.second - bishop.second); });
					}
					//Przypadek 2: King -> Figure -> Bishop - z prawej z do³u
					else if (kingPos.first - index.x < 0 && index.x - bishop.first < 0
						&& kingPos.second - index.y > 0 && index.y - bishop.second > 0)
					{
						sf::Vector2i tempIndex = { kingPos.first + 1, kingPos.second - 1 };

						while (tempIndex.x < bishop.first && tempIndex.y > bishop.second)
						{
							if (board.isOccupied({ tempIndex.x, tempIndex.y }) && index != tempIndex)
								return;
							++tempIndex.x;
							--tempIndex.y;
						}
						std::erase_if(movesCopy, [tempIndex, bishop](auto move) {return abs(move.first - bishop.first) != abs(move.second - bishop.second); });
					}
					//Przypadek 3: King -> Figure -> Bishop - z lewej z do³u
					else if (kingPos.first - index.x > 0 && index.x - bishop.first > 0
						&& kingPos.second - index.y > 0 && index.y - bishop.second > 0)
					{
						sf::Vector2i tempIndex = { kingPos.first - 1, kingPos.second - 1 };

						while (tempIndex.x > bishop.first && tempIndex.y > bishop.second)
						{
							if (board.isOccupied({ tempIndex.x, tempIndex.y }) && index != tempIndex)
								return;
							--tempIndex.x;
							--tempIndex.y;
						}
						std::erase_if(movesCopy, [tempIndex, bishop](auto move) {return abs(move.first - bishop.first) != abs(move.second - bishop.second); });
					}
					//Przypadek 4: King -> Figure -> Bishop - z lewej z góry
					else if (kingPos.first - index.x > 0 && index.x - bishop.first > 0
						&& kingPos.second - index.y < 0 && index.y - bishop.second < 0)
					{
						sf::Vector2i tempIndex = { kingPos.first - 1, kingPos.second + 1 };

						while (tempIndex.x > bishop.first && tempIndex.y < bishop.second)
						{
							if (board.isOccupied({ tempIndex.x, tempIndex.y }) && index != tempIndex)
								return;
							--tempIndex.x;
							++tempIndex.y;
						}
						std::erase_if(movesCopy, [bishop](auto move) {return abs(move.first - bishop.first) != abs(move.second - bishop.second); });
					}
				}
			});
	}

	moves = std::set<std::pair<int, int>>(movesCopy.begin(), movesCopy.end());
}

std::set<std::pair<int, int>> GameLogic::calculateDropMoves(figureType type, team t)
{
	std::set<std::pair<int, int>>  dropMoves;
	
	if (type == figureType::Pawn)
	{
		for (int i = 0; i < 9; i++)
		{
			std::set<std::pair<int, int>> row;
			for (int j = 0; j < 9; j++)
			{
				auto figType = board[i][j].getFigureType();
				if (figType.has_value() && figType.value() == figureType::Pawn && board[i][j].getTeam() == t)
				{
					row.clear();
					break;
				}
				row.insert({ i,j });
			}
			dropMoves.merge(row);
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				dropMoves.insert({ i,j });
			}
		}
	}

	filterBlockingCheckMoves(dropMoves, t);
	return dropMoves;
	//board.highligth(dropMoves, t, false);
}

std::set<std::pair<int, int>> GameLogic::possibleDrops(PiecesToDrop& dropField, team t)
{
	std::set<std::pair<int, int>> possibleDrops;
	if (dropField.getCount(1) > 0)
		possibleDrops.merge(calculateDropMoves(figureType::Pawn, t));

	for (int i = 1; i < 7; i++)
	{
		if (dropField.getCount(i) > 0)
		{
			possibleDrops.merge(calculateDropMoves(figureType::Rook, t));
		}
	}

	return possibleDrops;
}

std::set<std::pair<int, int>> GameLogic::calculatePossibleMoves(team t)
{
	calculateControledSquares(t, true);
	std::set<std::pair<int, int>> potentialMoves;
	if (t == team::White)
		potentialMoves = whitesControledSquares;
	else
		potentialMoves = blacksControledSquares;

	auto correctMoves = std::views::filter(potentialMoves, [this](auto move)
		{
			return !board.isOccupied({ move.first, move.second });
		});

	return std::set<std::pair<int, int>>(correctMoves.begin(), correctMoves.end());
}

bool GameLogic::checkIfMate(team t, PiecesToDrop& dropField)
{

	if (t == team::White && !blacksCheckingFigures.empty())
	{
		auto possibleMoves = calculatePossibleMoves(t);
		auto possibleDropMoves = possibleDrops(dropField, t);
		if (possibleMoves.empty() && possibleDropMoves.empty())
			return true;
		else
			return false;
	}
	else if(t == team::Black && !whitesCheckingFigures.empty())
	{
		auto possibleMoves = calculatePossibleMoves(t);
		auto possibleDropMoves = possibleDrops(dropField, t);
		if (possibleMoves.empty() && possibleDropMoves.empty())
			return true;
		else
			return false;
	}
	return false;
}

bool GameLogic::checkIfStalemate(team t, PiecesToDrop& dropField)
{
	if (t == team::White && blacksCheckingFigures.empty())
	{
		auto possibleMoves = calculatePossibleMoves(t);
		auto possibleDropMoves = possibleDrops(dropField, t);
		if (possibleMoves.empty() && possibleDropMoves.empty())
			return true;
		else
			return false;
	}
	else if (t == team::Black && whitesCheckingFigures.empty())
	{
		auto possibleMoves = calculatePossibleMoves(t);		
		auto possibleDropMoves = possibleDrops(dropField, t);
		if (possibleMoves.empty() && possibleDropMoves.empty())
			return true;
		else
			return false;
	}
	return false;
}

