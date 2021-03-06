#include "Board.h"

#define NOT_FOUND -1

Board::Board()
{
	auto txManager = TextureManager::getInstance();
	sf::Vector2f pos;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			pos.x = initialPos.x + i * (sqSize.x + sqSpacing);
			pos.y = initialPos.y - j * (sqSize.y + sqSpacing);

			Square temp;

			//Ustawianie figur po stronie bia造ch
			//Piony
			if (j == 2) //3. linia
			{
				temp = Square(sqSize, pos, std::make_unique<Pawn>(team::White, pos));
			}
			//1. linia
			else if (j == 0)
			{
				//Lance
				if (i == 0 || i == 8)
				{
					temp = Square(sqSize, pos, std::make_unique<Lance>(team::White, pos));
				}

				//Skoczki
				else if (i == 1 || i == 7)
				{
					temp = Square(sqSize, pos, std::make_unique<Knight>(team::White, pos));
				}

				//Srebrni genera這wie
				else if (i == 2 || i == 6)
				{
					temp = Square(sqSize, pos, std::make_unique<Silver>(team::White, pos));
				}

				//Z這ci genera這wie
				else if (i == 3 || i == 5)
				{
					temp = Square(sqSize, pos, std::make_unique<Golden>(team::White, pos));
				}

				//Kr鏊
				else if (i == 4)
				{
					temp = Square(sqSize, pos, std::make_unique<King>(team::White, pos));
				}

			}
			//2. linia
			else if (j == 1 && (i == 1 || i == 7))
			{
				//Goniec
				if (i == 1)
				{
					temp = Square(sqSize, pos, std::make_unique<Bishop>(team::White, pos));
				}

				//Wie瘸
				else if (i == 7)
				{
					temp = Square(sqSize, pos, std::make_unique<Rook>(team::White, pos));
				}
			}

			//Ustawianie figur po stronie czarnych
			//Piony
			else if (j == 6) //3. linia
			{
				temp = Square(sqSize, pos, std::make_unique<Pawn>(team::Black, pos));
			}
			//1. linia
			else if (j == 8)
			{
				//Lance
				if (i == 0 || i == 8)
				{
					temp = Square(sqSize, pos, std::make_unique<Lance>(team::Black, pos));
				}

				//Skoczki
				else if (i == 1 || i == 7)
				{
					temp = Square(sqSize, pos, std::make_unique<Knight>(team::Black, pos));
				}

				//Srebrni genera這wie
				else if (i == 2 || i == 6)
				{
					temp = Square(sqSize, pos, std::make_unique<Silver>(team::Black, pos));
				}

				//Z這ci genera這wie
				else if (i == 3 || i == 5)
				{
					temp = Square(sqSize, pos, std::make_unique<Golden>(team::Black, pos));
				}

				//Kr鏊
				else if (i == 4)
				{
					temp = Square(sqSize, pos, std::make_unique<King>(team::Black, pos));
				}

			}
			//2. linia
			else if (j == 7 && (i == 1 || i == 7))
			{
				//Goniec
				if (i == 1)
				{
					temp = Square(sqSize, pos, std::make_unique<Bishop>(team::Black, pos));
				}

				//Wie瘸
				else if (i == 7)
				{
					temp = Square(sqSize, pos, std::make_unique<Rook>(team::Black, pos));
				}
			}
			else
			{
				temp = Square(sqSize, pos);
			}
			
			squares[i][j] = std::move(temp);
		}
	}
}


std::optional<sf::Vector2i> Board::findSquare(sf::Vector2i cursorPos)
{
	sf::Vector2i foundSquareIndex = {NOT_FOUND, NOT_FOUND};

	for (int i = 0; i < squares.size(); i++)
	{
		if (cursorPos.x >= squares[i][0].getPos().x - sqSize.x / 2 &&
			cursorPos.x <= squares[i][0].getPos().x + sqSize.x / 2)
		{
			foundSquareIndex.x = i;
			break;
		}
	}

	if (foundSquareIndex.x == NOT_FOUND) //Kursor poza szachownic?
		return {};

	for (int i = 0; i < squares.size(); i++)
	{
		if (cursorPos.y >= squares[0][i].getPos().y - sqSize.y / 2 &&
			cursorPos.y <= squares[0][i].getPos().y + sqSize.y / 2)
		{
			foundSquareIndex.y = i;
			break;
		}
	}

	if (foundSquareIndex.y == NOT_FOUND) //Kursor poza szachownic?
		return {};
	
	return foundSquareIndex;
}

std::optional<figureType> Board::moveFigure(sf::Vector2i oldSq, sf::Vector2i newSq)
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

void Board::highligth(std::set<std::pair<int, int>> moves, team figureTeam, bool selector = true)
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