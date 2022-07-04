#pragma once
#include <SFML/Graphics.hpp>
#include <ranges>
#include <optional>
#include <utility>
#include <exception>
#include <array>
#include <memory>
#include "TextureManager.h"
#include "Bishop.h"
#include "Silver.h"
#include "Knight.h"
#include "Golden.h"
#include "Square.h"
#include "Figure.h"
#include "Lance.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"


class Board : public sf::Drawable
{
	sf::Vector2f initialPos{ 140, 810 }, sqSize{ 80,80 };
	float sqSpacing{ 3.f };
	std::array<std::array<Square, 9>, 9> squares;
	std::pair<int, int> whiteKingPos = { 4,0 }, blackKingPos = { 4,8 };

public:
	Board();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override
	{
		for (auto& column : squares)
		{
			for (auto& square : column)
			{
				target.draw(square, state);
			}
		}
	}

	std::optional<figureType> moveFigure(sf::Vector2i oldSq, sf::Vector2i newSq)
	{
		std::optional<figureType> takenFigureType = squares[newSq.x][newSq.y].getFigureType();

		squares[oldSq.x][oldSq.y].giveFigure(squares[newSq.x][newSq.y]);

		if (squares[newSq.x][newSq.y].getFigureType() == figureType::King)
		{
			if (squares[newSq.x][newSq.y].getTeam() == team::White)
				whiteKingPos = { newSq.x, newSq.y };
			else
				blackKingPos = { newSq.x, newSq.y };
		}

		return takenFigureType;
	}

	std::optional<sf::Vector2i> findSquare(sf::Vector2i cursorPos);

	bool isHighlighted(sf::Vector2i sqIndex)
	{
		return squares[sqIndex.x][sqIndex.y].isHighlighted();
	}

	void highligth(sf::Vector2i sqIndex)
	{
		squares[sqIndex.x][sqIndex.y].highlight();
	}

	void highligth(std::set<std::pair<int, int>> moves, team figureTeam , bool selector = true)
	{
		std::ranges::for_each(moves, [this, figureTeam, selector](std::pair<int, int> sq) {
			team sqTeam = squares[sq.first][sq.second].getTeam();
			if (selector)
			{
				if (sqTeam != figureTeam)
					squares[sq.first][sq.second].highlight();
			}
			else
			{
				if (!squares[sq.first][sq.second].isOccupied())
					squares[sq.first][sq.second].highlight();
			}
			});
	}

	void restoreAll()
	{
		for (auto& column : squares)
		{
			for (auto& sq : column)
			{
				sq.restoreColor();
			}
		}
	}

	std::array<Square,9>& operator[](int index)
	{
		return squares[index];
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalcFunc(sf::Vector2i Index)
	{
		return squares[Index.x][Index.y].getMovesCalcFunc();
	}

	void getFigure(sf::Vector2i index, std::unique_ptr<Figure>& droppedFigure)
	{
		squares[index.x][index.y].setFigure(droppedFigure);
	}

	void dropFigure(sf::Vector2i chosenSquare, std::unique_ptr<Figure> figurePtr)
	{
		squares[chosenSquare.x][chosenSquare.y].setFigure(figurePtr);
	}

	void promoteFigure(sf::Vector2i index)
	{
		squares[index.x][index.y].promoteFigure();
	}

	bool isPromoted(sf::Vector2i index)
	{
		return squares[index.x][index.y].isPromoted();
	}

	bool isOccupied(sf::Vector2i sqIndex)
	{
		return squares[sqIndex.x][sqIndex.y].isOccupied();
	}

	bool isWhite(sf::Vector2i index)
	{
		return squares[index.x][index.y].getTeam() == team::White;
	}

	bool isBlack(sf::Vector2i index)
	{
		return squares[index.x][index.y].getTeam() == team::Black;
	}

	std::pair<int, int> getKingPos(team t)
	{
		if (t == team::White)
			return whiteKingPos;
		else
			return blackKingPos;
	}
};

