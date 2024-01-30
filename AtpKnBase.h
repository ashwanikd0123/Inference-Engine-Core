#pragma once
#include "AtpToken.h"
#include <vector>
#include <iterator>
#include <stack>
#include <iostream>
#include <unordered_map>
#include "AtpStatement.h"
/*
* special predicate will be used for storing equality among AtpTerms
* equality will act as relation like other predicates
* to support this following axioms must be included in KB
* these correspond to Reflexivity, Symmetry and Transitivity
* ![X] : (X = X)
* ![X,Y] : (X = Y => Y = X)
* ![X,Y,Z] : ((X = Y & Y = Z) => X = Z)
*/
const std::string equalityPredicate = "@equality@";
const std::string unequalityPredicate = "@notequality@";

class AtpKnBase
{
public:
	int counter;

	std::vector<AtpStatement*> axioms;
	std::vector<AtpStatement*> conjenctures;
	std::vector<AtpFunctor*> functors;

	std::unordered_map<std::string, AtpFunctor*> varMap;

	void init();
	void addAxiom(AtpStatement& statement);
	void addConjencture(AtpStatement& statement);
	void parseFormula(std::vector<AtpToken>& tokens);
};


