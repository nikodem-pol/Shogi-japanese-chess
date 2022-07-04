#pragma once
#include "TextureManager.h"
#include "BishopMovesCalculator.h"
#include "PromotedBishopMovesCalculator.h"
#include "Figure.h"


class Bishop : public Figure
{
public:
	Bishop(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("bishop"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedBishop"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<BishopMovesCalculator>(this->figureTeam);

	}

	Bishop(team fTeam)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("bishop"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedBishop"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition({0,0});

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<BishopMovesCalculator>(this->figureTeam);
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	figureType getFigureType() override
	{
		return figureType::Bishop;
	}

	void promote() override
	{
		//Zmiana funkcji licz¹cej ruchy
		this->movesCalcFunction.reset(new PromotedBishopMovesCalculator(this->figureTeam));

		auto txManager = TextureManager::getInstance();

		auto currentFigurePosition = this->figure.getPosition();

		if (this->figureTeam == team::White)
			this->figure.setTexture(txManager->getTx("promotedBishop"));

		else //team::Black
			this->figure.setTexture(txManager->getTx("reversedPromotedBishop"));

		this->figure.setOrigin(figDimensions.x / 2, figDimensions.y / 2);
		this->figure.setPosition(currentFigurePosition);

		promoted = true;
	}
};
