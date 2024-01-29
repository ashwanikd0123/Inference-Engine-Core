#pragma once
#include "AtpFormula.h"

enum AtpStatementType {
	AXIOM,
	CONJENCTURE
};

class AtpStatement
{
public:
	int value;
	std::string name;
	
	std::vector<AtpFunctor> functors;
	AtpFormula formula;
	AtpStatementType type;
};

