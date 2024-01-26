#pragma once
#include "AtpToken.h"
#include <vector>
#include <iterator>
#include <stack>
#include <iostream>
#include <unordered_map>
#include "AtpStatement.h"

class AtpKnBase
{
	std::set<AtpStatement> axioms;
	std::set<AtpStatement> conjenctures;
	std::unordered_map<AtpTerm, std::string> termMap;
	std::unordered_map<std::string, AtpTerm> varMap;

public:
	void init();
	void addAxiom(AtpStatement statement);
	void addConjencture(AtpStatement statement);
	void parseFormula(std::vector<AtpToken> tokens);
};


