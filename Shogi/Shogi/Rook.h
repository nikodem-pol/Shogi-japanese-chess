#pragma once
#include "TextureManager.h"
#include "RookMovesCalculator.h"
#include "PromotedRookMovesCalculator.h"
#include "Figure.h"


class Rook : public Figure
{
public:
	Rook(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("rook"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedRook"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<RookMovesCalculator>(this->figureTeam);
	}
	

	Rook(team fTeam)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("rook"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedRook"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition({0,0});

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<RookMovesCalculator>(this->figureTeam);
	
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	figureType getFigureType() override
	{
		return figureType::Rook;
	}

	void promote() override
	{
		//Zmiana funkcji licz¹cej ruchy
		this->movesCalcFunction.reset(new PromotedRookMovesCalculator(this->figureTeam));

		auto txManager = TextureManager::getInstance();

		auto currentFigurePosition = this->figure.getPosition();

		if (this->figureTeam == team::White)
			this->figure.setTexture(txManager->getTx("promotedRook"));

		else //team::Black
			this->figure.setTexture(txManager->getTx("reversedPromotedRook"));

		this->figure.setOrigin(figDimensions.x / 2, figDimensions.y / 2);
		this->figure.setPosition(currentFigurePosition);
		promoted = true;
	}
};
