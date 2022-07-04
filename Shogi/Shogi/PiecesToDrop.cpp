#include "PiecesToDrop.h"

PiecesToDrop::PiecesToDrop(sf::Vector2f pos, enum class team _team) : team(_team)
{
	dropSquares[0] = DropSquare('P', pos);
	dropSquares[1] = DropSquare('L', { pos.x + 40 + 10, pos.y });
	dropSquares[2] = DropSquare('N', { pos.x + 80 + 20, pos.y });
	dropSquares[3] = DropSquare('B', { pos.x + 120 + 30, pos.y });
	dropSquares[4] = DropSquare('R', { pos.x + 25, pos.y + 70 });
	dropSquares[5] = DropSquare('S', { pos.x + 65 + 10, pos.y + 70 });
	dropSquares[6] = DropSquare('G', { pos.x + 105 + 20, pos.y + 70});
}

void PiecesToDrop::getFigure(figureType type)
{
	switch (type)
	{
	case figureType::Pawn:
		dropSquares[0].incrementFigureCounter();
		break;
	case figureType::Lance:
		dropSquares[1].incrementFigureCounter();
		break;
	case figureType::Knight:
		dropSquares[2].incrementFigureCounter();
		break;
	case figureType::Bishop:
		dropSquares[3].incrementFigureCounter();
		break;
	case figureType::Rook:
		dropSquares[4].incrementFigureCounter();
		break;
	case figureType::Silver:
		dropSquares[5].incrementFigureCounter();
		break;
	case figureType::Golden:
		dropSquares[6].incrementFigureCounter();
		break;
	default:
		break;
	}
}

std::optional<int> PiecesToDrop::findSquare(sf::Vector2i mousePos)
{
	for (int i = 0; i < 7; i++)
	{
		if (mousePos.x >= dropSquares[i].getPosition().x - dropSquares[i].getSquareSize().x / 2
			&& mousePos.x <= dropSquares[i].getPosition().x + dropSquares[i].getSquareSize().x / 2
			&& mousePos.y >= dropSquares[i].getPosition().y - dropSquares[i].getSquareSize().y / 2
			&& mousePos.y <= dropSquares[i].getPosition().y + dropSquares[i].getSquareSize().y / 2)
		{
			if (dropSquares[i].isAvailableToDrop())
			{
				dropSquares[i].highligth();
				return { i };
			}
			else
				return{};
		}
	}

	return {};
}

std::unique_ptr<Figure> PiecesToDrop::dropFigure(int index)
{
	std::unique_ptr<Figure> droppedFigure;
	//char symbol = dropSquares[index].getFigureSymbol();
	switch (index)
	{
	case 0:
		dropSquares[0].decrementFigureCounter();
		droppedFigure = std::make_unique<Pawn>(this->team);
		return droppedFigure;
		break;
	case 1:
		dropSquares[1].decrementFigureCounter();
		droppedFigure = std::make_unique<Lance>(this->team);
		return droppedFigure;
		break;
	case 2:
		dropSquares[2].decrementFigureCounter();
		droppedFigure = std::make_unique<Knight>(this->team);
		return droppedFigure;
		break;
	case 3:
		dropSquares[3].decrementFigureCounter();
		droppedFigure = std::make_unique<Bishop>(this->team);
		return droppedFigure;
		break;
	case 4:
		dropSquares[4].decrementFigureCounter();
		droppedFigure = std::make_unique<Rook>(this->team);
		return droppedFigure;
		break;
	case 5:
		dropSquares[5].decrementFigureCounter();
		droppedFigure = std::make_unique<Silver>(this->team);
		return droppedFigure;
		break;
	case 6:
		dropSquares[6].decrementFigureCounter();
		droppedFigure = std::make_unique<Golden>(this->team);
		return droppedFigure;
		break;
	default:
		break;
	}
}

void PiecesToDrop::restoreSquareColor(int index)
{
	dropSquares[index].restoreColor();
}

void PiecesToDrop::draw(sf::RenderTarget& target, sf::RenderStates state) const 
{
	for (int i = 0; i < 7; i++)
	{
		target.draw(dropSquares[i], state);
	}
}

figureType PiecesToDrop::getFigureType(int index)
{
	switch (index)
	{
	case 0:
		return figureType::Pawn;
	case 1:
		return figureType::Lance;
	case 2:
		return figureType::Knight;
	case 3:
		return figureType::Bishop;
	case 4:
		return figureType::Rook;
	case 5:
		return figureType::Silver;
	case 6:
		return figureType::Golden;
	default:
		return figureType::Pawn;
		break;
	}
}
