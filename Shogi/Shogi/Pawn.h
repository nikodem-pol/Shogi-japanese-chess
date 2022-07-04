#pragma once
#include "PawnMovesCalculator.h"
#include "GoldenMovesCalculator.h"
#include "TextureManager.h"
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(team fTeam, sf::Vector2f pos)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("pawn"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedPawn"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition(pos);

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<PawnMovesCalculator>(this->figureTeam);
	}

	Pawn(team fTeam)
	{
		//Przydzia³ do dru¿yny
		this->figureTeam = fTeam;

		//£adowanie odp tekstury
		auto txManager = TextureManager::getInstance();

		if (fTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("pawn"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedPawn"));

		//Ustawianie odp pozycji na szachownicy
		this->figure.setOrigin(this->figDimensions.x / 2, this->figDimensions.y / 2);
		this->figure.setPosition({0,0});

		//Funkcja licz¹ca ruchy
		this->movesCalcFunction = std::make_shared<PawnMovesCalculator>(this->figureTeam);
	}

	figureType getFigureType() override
	{
		return figureType::Pawn;
	}

	std::shared_ptr<MovesCalculationFunction> getMovesCalculationFunc() const override
	{
		return this->movesCalcFunction;
	}

	void promote() override
	{

		//Zmiana funkcji licz¹cej ruchy
		this->movesCalcFunction.reset(new GoldenMovesCalculator(this->figureTeam));

		auto txManager = TextureManager::getInstance();

		auto currentFigurePosition = this->figure.getPosition();

		if (this->figureTeam == team::White)
			this->figure = sf::Sprite(txManager->getTx("promotedPawn"));

		else //team::Black
			this->figure = sf::Sprite(txManager->getTx("reversedPromotedPawn"));
		

		this->figure.setOrigin(figDimensions.x / 2, figDimensions.y / 2);
		this->figure.setPosition(currentFigurePosition);
		promoted = true;

	}
};

