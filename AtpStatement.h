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
	
	std::set<AtpTerm> terms;
	AtpFormula formula;
	AtpStatementType type;

	// operator overloading
	bool operator==(const AtpStatement& statement) const
	{
		if (this->terms.size() != statement.terms.size()) {
			return false;
		}

		for (auto& t : terms) {
			if (statement.terms.find(t) == statement.terms.end()) {
				return false;
			}
		}

		return this->formula == statement.formula;
	}

	bool operator>(const AtpStatement& statement) const
	{
		return this->value > statement.value;
	}

	bool operator<(const AtpStatement& statement) const
	{
		return this->value < statement.value;
	}
};

