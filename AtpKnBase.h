#pragma once
#include "AtpToken.h"
#include <vector>
#include <unordered_map>
#include "AtpStatement.h"

class AtpKnBase
{
	std::set<AtpStatement> statements;
	std::unordered_map<AtpTerm, std::string> termMap;
	std::unordered_map<std::string, AtpTerm> varMap;

public:
	void init();
	void parseFormula(std::vector<AtpToken> tokens);
};

