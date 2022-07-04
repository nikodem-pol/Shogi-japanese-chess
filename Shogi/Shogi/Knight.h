#pragma once
#include "TextureManager.h"
#include "KnightMovesCalculator.h"
#include "GoldenMovesCalculator.h"
#include "Figure.h"


class Knight : public Figure
{
public:
	Knight(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("knight"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedKnight"));
		
		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<KnightMovesCalculator>(this->figureTeam);
	}

	Knight(team fTeam)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("knight"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedKnight"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition({0,0});

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<KnightMovesCalculator>(this->figureTeam);
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	figureType getFigureType() override
	{
		return figureType::Knight;
	}

	void promote() override
	{
		//Zmiana funkcji licz¹cej ruchy
		this->movesCalcFunction.reset(new GoldenMovesCalculator(this->figureTeam));

		auto txManager = TextureManager::getInstance();

		auto currentFigurePosition = this->figure.getPosition();

		if (this->figureTeam == team::White)
			this->figure.setTexture(txManager->getTx("promotedKnight"));

		else //team::Black
			this->figure.setTexture(txManager->getTx("reversedPromotedKnight"));

		this->figure.setOrigin(figDimensions.x / 2, figDimensions.y / 2);
		this->figure.setPosition(currentFigurePosition);

		promoted = true;
	}
};
