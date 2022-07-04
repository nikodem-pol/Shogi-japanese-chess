#pragma once
#include <set>
#include <vector>
#include <future>
#include <utility>
#include <ranges>
#include "SFML/Graphics.hpp"
#include "PiecesToDrop.h"
#include "Board.h"
#include "Enums.h"

class GameLogic
{
	Board& board;
	std::set<std::pair<int, int>> whitesControledSquares;
	std::set<std::pair<int, int>> blacksControledSquares;
	std::set<std::pair<int, int>> whitesCheckingFigures;
	std::set<std::pair<int, int>> blacksCheckingFigures;

	std::set<std::pair<int, int>> calculateBishopAndRookMoves(sf::Vector2i index, std::shared_ptr<MovesCalculationFunction> calcFunc);
	std::set<std::pair<int, int>> calculateLanceMoves(sf::Vector2i index, std::shared_ptr<MovesCalculationFunction> calcFunc);
	std::set<std::pair<int, int>> calculateKingMoves(sf::Vector2i index, std::shared_ptr<MovesCalculationFunction> calcFunc);
	std::set<std::pair<int, int>> checkUpMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkDownMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkRightMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkLeftMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkUpperRightMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkUpperLeftMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkLowerRightMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> checkLowerLeftMoves(sf::Vector2i index, std::set<std::pair<int, int>> moves);
	std::set<std::pair<int, int>> calculate(std::array<Square, 9>& column, int rowNum, team t, bool selector = false);
	std::set<std::pair<int, int>> calculateMoves(sf::Vector2i Index);
	void filterBlockingCheckMoves(std::set<std::pair<int, int>>& moves, team t);
	void calculatePinnedFigureMoves(sf::Vector2i index,std::set<std::pair<int, int>>& moves, team t);
	std::set<std::pair<int, int>> possibleDrops(PiecesToDrop& dropField, team t);
	std::set<std::pair<int, int>> calculatePossibleMoves(team t);
public:
	std::set<std::pair<int,int>> calculateDropMoves(figureType type, team t);
	void calculateControledSquares(team, bool selector = false);
	void highlightCorrectMoves(sf::Vector2i index);
	bool checkIfMate(team t, PiecesToDrop& dropField);
	bool checkIfStalemate(team t, PiecesToDrop& dropField);
	GameLogic(Board& b) : board(b) {}
};

