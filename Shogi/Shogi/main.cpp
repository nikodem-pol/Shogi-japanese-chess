#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <variant>
#include <thread>
#include <chrono>
#include <string>
#include <atomic>
#include <memory>
#include "TextureManager.h"
#include "GameLogic.h"
#include "game_states.h"
#include "Board.h"
#include "Square.h"
#include "DropSquare.h"
#include "PiecesToDrop.h"
#include "PromotingWidget.h"
#include "RookMovesCalculator.h"
#include "DecisionWindow.h"


std::pair<sf::RectangleShape, sf::Text> getNewGameButton(sf::Vector2f pos, sf::Vector2f size)
{
	
	auto fontManager = FontManager::getInstance();
	sf::RectangleShape newGameButton;
	newGameButton.setFillColor(sf::Color::White);
	newGameButton.setSize(size);
	newGameButton.setPosition(pos);
	sf::Text newGameText;
	newGameText.setFont(fontManager->getFont());
	newGameText.setCharacterSize(24);
	newGameText.setFillColor(sf::Color::Black);
	newGameText.setStyle(sf::Text::Bold);
	newGameText.setString("New game");
	auto newGameTextRect = newGameText.getLocalBounds();
	newGameText.setOrigin(newGameTextRect.left + newGameTextRect.width / 2,
		newGameTextRect.top + newGameTextRect.height / 2);
	newGameText.setPosition({ pos.x + size.x / 2, pos.y + size.y / 2 });

	return std::make_pair(newGameButton, newGameText);
}

int main()
{
	//Tworzenie oknapole
	sf::RenderWindow  window(sf::VideoMode(1200, 950), "Shogi", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);

	//Obiekt dostêpu do zdarzeñ
	sf::Event event;
	
	bool play = true;
	while (play)
	{
		//Generacja szachownicy
		Board board;
		GameLogic game(board);

		//Przycisk nowa gra
		sf::Vector2f newGameButtonSize = { 135,60 }, newGameButtonPos = { 1040, 20 };
		auto newGameButton = getNewGameButton(newGameButtonPos, newGameButtonSize);

		std::optional<DecisionWindow> wid;

		std::optional<PromotingWidget> promotionWidget;
		PiecesToDrop whitesDropField({ 900,692 }, team::White);
		PiecesToDrop blacksDropField({ 900, 190 }, team::Black);
		bool skipClick = false;
		bool newgame = false;
		std::optional<sf::Vector2i> fromSq, toSq;
		std::optional<int> chosenDropSq;
		//Pierwszy stan gry - zaczyaj¹ bia³e
		using gameState = std::variant<state::whiteChFig, state::whiteChoosingDest, state::blackChoosingDest, state::blackChFig, state::promoting, state::endGameOrNewGameDecision>;
		gameState currentState = state::whiteChFig();


		while (true)
		{
			if (newgame)
				break;
			//Czyszczenie okna
			window.clear(sf::Color::Black);

			//Pobieranie zdarzenia 
			//ze szczytu kolejki zdarzeñ
			window.pollEvent(event);

			//Event -> Zamkniêcie okna
			if (event.type == sf::Event::Closed)
			{
				play = false;
				break;
			}

			//Event -> Klikniêcie przyciskiem myszy
			if (event.type == sf::Event::MouseButtonPressed || skipClick)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				sf::Vector2i mousePos = { event.mouseButton.x, event.mouseButton.y };

				if (event.mouseButton.button == sf::Mouse::Left || skipClick)
				{

					currentState = state::match(currentState,

					////////////////////////////////////////////////////////////////////////////////////////////////////
					//Bia³e wybieraja figurê
					[mousePos, &chosenDropSq, &fromSq, &board, &whitesDropField, &game, newGameButtonPos, newGameButtonSize, &skipClick](state::whiteChFig& st) -> gameState
						{
							///////////////////////
							game.calculateControledSquares(team::Black);
							if (game.checkIfMate(team::White, whitesDropField))
							{
								skipClick = true;
								return state::endGameOrNewGameDecision(team::White, state::reason::mate);
							}
								
							if (game.checkIfStalemate(team::White, whitesDropField))
							{
								skipClick = true;
								return state::endGameOrNewGameDecision(team::White, state::reason::stalemate);
							}
							////////////////////
							fromSq = board.findSquare(mousePos);
							chosenDropSq = whitesDropField.findSquare(mousePos);
							if (fromSq.has_value()
								&& board.isOccupied(fromSq.value())
								&& board.isWhite(fromSq.value()))
							{
								board.highligth(fromSq.value());
								//game.calculateControledSquares(team::Black);
								game.highlightCorrectMoves(fromSq.value());

								//Zmiana stanu
								return state::whiteChoosingDest();
							}
							else if (chosenDropSq.has_value())
							{
								//game.calculateControledSquares(team::Black);
								board.highligth(game.calculateDropMoves(whitesDropField.getFigureType(chosenDropSq.value()), team::White), team::White, false);
								return state::whiteChoosingDest();
							}
							else if (mousePos.x > newGameButtonPos.x && mousePos.x < newGameButtonPos.x + newGameButtonSize.x
								&& mousePos.y > newGameButtonPos.y && mousePos.y < newGameButtonPos.y + newGameButtonSize.y)
							{
								skipClick = true;
								return state::endGameOrNewGameDecision(team::White, state::reason::newGame);
							}
							else
								//Brak zmiany stanu
								return st;
						},

					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//Bia³e wybieraj¹ pole dla figury
					[mousePos, &chosenDropSq, &fromSq, &toSq, &board, &whitesDropField, &skipClick](state::whiteChoosingDest& st) -> gameState
						{
							toSq = board.findSquare(mousePos);
							std::optional<figureType> potentialTakenFigureType;

							if (toSq.has_value() && fromSq.has_value() && fromSq != toSq /*&& board.isHighlighted(toSq.value())*/)
							{
								potentialTakenFigureType = board.moveFigure(fromSq.value(), toSq.value());

								if (potentialTakenFigureType.has_value())
									whitesDropField.getFigure(potentialTakenFigureType.value());

								board.restoreAll();
								fromSq.reset();

								if (toSq.value().y >= 6 && !board.isPromoted(toSq.value()))
								{
									skipClick = true;
									return state::promoting(team::White);
								}

								toSq.reset();
								return state::blackChFig();
							}
							else if (chosenDropSq.has_value() && toSq.has_value())
							{
								board.restoreAll();
								board.dropFigure(toSq.value(), whitesDropField.dropFigure(chosenDropSq.value()));
								whitesDropField.restoreSquareColor(chosenDropSq.value());
								chosenDropSq.reset();
								return state::blackChFig();
							}
							else if (!toSq.has_value() && chosenDropSq.has_value())
							{
								board.restoreAll();
								whitesDropField.restoreSquareColor(chosenDropSq.value());
								chosenDropSq.reset();
								fromSq.reset();
								toSq.reset();
								return state::whiteChFig();
							}
							else
							{
								board.restoreAll();
								chosenDropSq.reset();
								fromSq.reset();
								toSq.reset();
								return state::whiteChFig();
							}

							return st;

						},

					///////////////////////////////////////////////////////////////////////////////////////////////////
					//Czarne wybieraja figurê
					[mousePos, &fromSq, &board, &chosenDropSq, &blacksDropField, &game, &skipClick, newGameButtonPos, newGameButtonSize](state::blackChFig& st) -> gameState
						{
							game.calculateControledSquares(team::White);
							if (game.checkIfMate(team::Black, blacksDropField))
							{
								skipClick = true;
								return state::endGameOrNewGameDecision(team::Black, state::reason::mate);
							}

							if (game.checkIfStalemate(team::White, blacksDropField))
							{
								skipClick = true;
								return state::endGameOrNewGameDecision(team::Black, state::reason::stalemate);
							}
							fromSq = board.findSquare(mousePos);
							chosenDropSq = blacksDropField.findSquare(mousePos);
							if (fromSq.has_value()
								&& board.isOccupied(fromSq.value())
								&& board.isBlack(fromSq.value()))
							{
								board.highligth(fromSq.value());
								game.calculateControledSquares(team::White);
								game.highlightCorrectMoves(fromSq.value());

								//Zmiana stanu
								return state::blackChoosingDest();
							}
							else if (chosenDropSq.has_value())
							{
								game.calculateControledSquares(team::White);
								board.highligth(game.calculateDropMoves(blacksDropField.getFigureType(chosenDropSq.value()), team::Black), team::Black, false);
								return state::blackChoosingDest();
							}
							else if (mousePos.x > newGameButtonPos.x && mousePos.x < newGameButtonPos.x + newGameButtonSize.x
								&& mousePos.y > newGameButtonPos.y && mousePos.y < newGameButtonPos.y + newGameButtonSize.y)
							{
								skipClick = true;
								return state::endGameOrNewGameDecision(team::Black, state::reason::newGame);
							}
							else
								//Brak zmiany stanu
								return st;
						},

					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//Czarne wybieraj¹ pole dla figury
					[mousePos, &fromSq, &toSq, &board, &blacksDropField, &chosenDropSq, &skipClick](state::blackChoosingDest& st) -> gameState
						{
							toSq = board.findSquare(mousePos);
							std::optional<figureType> potentialTakenFigureType;

							if (toSq.has_value() && fromSq.has_value() && fromSq != toSq /*&& board.isHighlighted(toSq.value())*/)
							{
								potentialTakenFigureType = board.moveFigure(fromSq.value(), toSq.value());

								if (potentialTakenFigureType.has_value())
									blacksDropField.getFigure(potentialTakenFigureType.value());

								board.restoreAll();
								fromSq.reset();
								if (toSq.value().y <= 2 && !board.isPromoted(toSq.value()))
								{
									skipClick = true;
									return state::promoting(team::White);
								}
								toSq.reset();
								return state::whiteChFig();
							}
							else if (chosenDropSq.has_value() && toSq.has_value())
							{
								board.restoreAll();
								board.dropFigure(toSq.value(), blacksDropField.dropFigure(chosenDropSq.value()));
								blacksDropField.restoreSquareColor(chosenDropSq.value());
								chosenDropSq.reset();
								return state::whiteChFig();
							}
							else if (!toSq.has_value() && chosenDropSq.has_value())
							{
								board.restoreAll();
								blacksDropField.restoreSquareColor(chosenDropSq.value());
								chosenDropSq.reset();
								fromSq.reset();
								toSq.reset();
								return state::blackChFig();
							}
							else
							{
								board.restoreAll();
								chosenDropSq.reset();
								fromSq.reset();
								toSq.reset();
								return state::blackChFig();
							}

							return st;
						},

					///////////////////////////////////////////////////////////////////////////////////////
					//Promowanie figur
					[mousePos, &promotionWidget, &toSq, &board, &skipClick](state::promoting& st) -> gameState
						{
							skipClick = false;
							if (board.isWhite(toSq.value()))
							{
								promotionWidget = PromotingWidget({ 970, 590 }, "Promote", "Decline");
								std::optional<bool> decision = promotionWidget.value().getDecision(mousePos);
								if (decision.has_value())
								{
									if (decision.value())
									{
										board.promoteFigure(toSq.value());
									}

									promotionWidget.reset();

									return state::blackChFig();
								}
								else
								{
									return st;
								}
							}
							else
							{
								promotionWidget = PromotingWidget({ 970, 380 }, "Promote", "Decline");
								std::optional<bool> decision = promotionWidget.value().getDecision(mousePos);
								if (decision.has_value())
								{
									if (decision.value())
									{
										board.promoteFigure(toSq.value());
									}

									promotionWidget.reset();

									return state::whiteChFig();
								}
								else
								{
									return st;
								}
							}
							return  st;
						},

					///////////////////////////////////////////////////////////////////////////////////////
					//Nowa gra lub koniec gry
					[mousePos, &wid, &skipClick, &newgame, &play](state::endGameOrNewGameDecision& st) -> gameState
					{
							if (st.reasonOfCalling == state::reason::newGame)
							{
								wid = DecisionWindow({ 600, 475 }, "Do you want to start a new game?");
								auto decision = wid.value().getDecision(mousePos);
								if (decision.has_value() && decision.value())
								{
									skipClick = false;
									newgame = true;
								}
								else if (decision.has_value() && !decision.value())
								{
									skipClick = false;
									wid.reset();
									if (st.t == team::White)
										return state::whiteChFig();
									else
										return state::blackChFig();
								}
								else
									return st;
							}
							else if (st.reasonOfCalling == state::reason::mate)
							{
								if (st.t == team::White)
								{
									wid = DecisionWindow({ 600, 475 }, "          Player2 won by mate.\n Do you want to start a new game ? ");
								}
								else
									wid = DecisionWindow({ 600, 475 }, "          Player1 won by mate.\n Do you want to start a new game ? ");

								auto decision = wid.value().getDecision(mousePos);
								if (decision.has_value() && decision.value())
								{
									skipClick = false;
									newgame = true;
								}
								else if (decision.has_value() && !decision.value())
								{
									newgame = true;
									play = false;
								}
								else
									return st;
							}
							else if (st.reasonOfCalling == state::reason::stalemate)
							{
								wid = DecisionWindow({ 600, 475 }, "               Draw\n Do you want to start a new game ? ");

								auto decision = wid.value().getDecision(mousePos);
								if (decision.has_value() && decision.value())
								{
									skipClick = false;
									newgame = true;
								}
								else if (decision.has_value() && !decision.value())
								{
									newgame = true;
									play = false;
								}
								else
									return st;
							}
							return st;
					});
				}
			}

			window.draw(board);
			window.draw(whitesDropField);
			window.draw(blacksDropField);
			window.draw(newGameButton.first);
			window.draw(newGameButton.second);
			if (wid.has_value())
				window.draw(wid.value());
			if (promotionWidget.has_value())
			{
				window.draw(promotionWidget.value());
			}

			window.display();
		}
	}
	return 0;
}