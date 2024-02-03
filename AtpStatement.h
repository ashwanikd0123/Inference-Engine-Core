#pragma once
#include "AtpFormula.h"
#include <unordered_map>
enum AtpStatementType {
	AXIOM,
	CONJENCTURE
};

class AtpStatement
{
public:
	int value;
	std::string name;
	
	AtpFormula *formula;
	AtpStatementType type;

	std::vector<AtpFormula*> formulas;
	std::unordered_map<std::string, AtpFunctor*> varMap;

	AtpStatement() {
		formula = new AtpFormula();
	}
};

