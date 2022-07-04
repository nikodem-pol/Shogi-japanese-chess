#pragma once
#include "TextureManager.h"
#include "GoldenMovesCalculator.h"
#include "Figure.h"


class Golden : public Figure
{
public:
	Golden(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("golden"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedGolden"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<GoldenMovesCalculator>(this->figureTeam);
	}

	Golden(team fTeam)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("golden"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedGolden"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition({0,0});

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<GoldenMovesCalculator>(this->figureTeam);
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	figureType getFigureType() override
	{
		return figureType::Golden;
	}

	void promote() override
	{
		return;
	}
};