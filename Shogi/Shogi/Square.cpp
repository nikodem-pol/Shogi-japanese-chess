#include "Square.h"


Square::Square(sf::Vector2f size, sf::Vector2f pos) : highlighted(false)
{
	shape.setPosition(pos);
	shape.setSize(size);
	shape.setOrigin(size.x / 2, size.y / 2);
	shape.setFillColor(sqColor);
	figure.reset(nullptr);
}

Square::Square(Square&& other) noexcept
{
	shape = std::move(other.shape);
	sqColor = std::move(other.sqColor);
	figure = std::move(other.figure);
	highlighted = std::move(other.highlighted);
	
}

Square& Square::operator=(Square&& other) noexcept
{
	shape = std::move(other.shape);
	sqColor = std::move(other.sqColor);
	figure = std::move(other.figure);
	highlighted = std::move(other.highlighted);
	return *this;
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(shape, state);
	if (figure != nullptr)
	{
		target.draw(*figure, state);
	}
}

std::optional<figureType> Square::getFigureType()
{
	if (figure != nullptr)
	{
		std::optional<figureType> typeOfHeldFigure = figure->getFigureType();
		return typeOfHeldFigure;
	}
	else
		return {};
}

/*
*	Bicie figure z pola chosenSq
*/
void Square::takes(Square & chosenSq)
{
	std::unique_ptr<Figure> figureToDelete = nullptr;
	//wymiana figurami
	figure.swap(chosenSq.figure);

	//Czyszczenie pola
	figure.swap(figureToDelete);

}

/*
*	Przemieszczanie figury na wolne pole
*/
void Square::giveFigure(Square& chosenSq)
{
	//
	chosenSq.figure = std::move(this->figure);
	chosenSq.figure->changePos(chosenSq.getPos());
	//
}