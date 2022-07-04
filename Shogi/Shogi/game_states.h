#pragma once
#include <variant>
#include <utility>
#include "Figure.h"

template<class... Ts> 
struct overloaded : Ts... { using Ts::operator()...; };

namespace state
{
	enum class reason{mate, stalemate, newGame};
	struct whiteChFig
	{};

	struct blackChFig
	{};

	struct whiteChoosingDest
	{};

	struct blackChoosingDest
	{};

	struct promoting
	{
		team promoting_team;
		promoting(team t) : promoting_team(t){}
	};

	struct endGameOrNewGameDecision
	{
		reason reasonOfCalling;
		team t;
		endGameOrNewGameDecision(team _t, reason r) : t(_t), reasonOfCalling(r) {}
	};

	template <typename Variant, typename... Matchers>
	auto match(Variant&& variant, Matchers&&... matchers)
	{
		return std::visit(
			overloaded{ std::forward<Matchers>(matchers)... },
			std::forward<Variant>(variant));
	}
}