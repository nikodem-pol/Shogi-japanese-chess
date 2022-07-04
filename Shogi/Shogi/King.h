#pragma once
#include "TextureManager.h"
#include "KingMovesCalculator.h"
#include "Figure.h"


class King : public Figure
{
public:
	King(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("king"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedKing"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<KingMovesCalculator>(this->figureTeam);
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	figureType getFigureType() override
	{
		return figureType::King;
	}

	void promote() override
	{
		return;
	}
};