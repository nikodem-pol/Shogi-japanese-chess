#pragma once
#include "TextureManager.h"
#include "LanceMovesCalculator.h"
#include "GoldenMovesCalculator.h"
#include "Figure.h"


class Lance : public Figure
{
public:
	Lance(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("lance"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedLance"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<LanceMovesCalculator>(this->figureTeam);

	}

	Lance(team fTeam)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("lance"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedLance"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition({0,0});

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<LanceMovesCalculator>(this->figureTeam);

	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	figureType getFigureType() override
	{
		return figureType::Lance;
	}

	void promote() override
	{
		//Zmiana funkcji licz¹cej ruchy
		this->movesCalcFunction.reset(new GoldenMovesCalculator(this->figureTeam));

		auto txManager = TextureManager::getInstance();

		auto currentFigurePosition = this->figure.getPosition();

		if (this->figureTeam == team::White)
			this->figure.setTexture(txManager->getTx("promotedLance"));

		else //team::Black
			this->figure.setTexture(txManager->getTx("reversedPromotedLance"));

		this->figure.setOrigin(figDimensions.x / 2, figDimensions.y / 2);
		this->figure.setPosition(currentFigurePosition);
		promoted = true;

	}

};
