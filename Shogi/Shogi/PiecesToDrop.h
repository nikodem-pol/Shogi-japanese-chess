#pragma once
#include <vector>
#include <optional>
#include <memory>
#include "SFML/Graphics.hpp"
#include "DropSquare.h"
#include "Bishop.h"
#include "Rook.h"
#include "Pawn.h"
#include "Knight.h"
#include "Lance.h"
#include "King.h"
#include "Golden.h"
#include "Silver.h"

class PiecesToDrop : public sf::Drawable
{
	DropSquare dropSquares[7];
	sf::Vector2f position;
	team team;
public:
	PiecesToDrop(sf::Vector2f position, enum class team team);
	~PiecesToDrop() = default;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	std::optional<int> findSquare(sf::Vector2i mousePos);
	std::unique_ptr<Figure> dropFigure(int index);
	void getFigure(figureType type);
	void restoreSquareColor(int index);
	int getCount(int index) { if (index > 0 && index < 7) return dropSquares[index].getFigureCounter(); }
	figureType getFigureType(int index);
};

