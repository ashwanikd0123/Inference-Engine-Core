#pragma once
#include "AtpLiteral.h"

class AtpFormula
{
public:
	int value;

	std::set<AtpLiteral> literals;

	bool operator==(const AtpFormula& formula) const {
		if (this->literals.size() != formula.literals.size()) {
			return false;
		}

		for (auto& l : this->literals) {
			if (formula.literals.find(l) == formula.literals.end()) {
				return false;
			}
 		}

		return true;
	}

	bool operator<(const AtpFormula& formula) const {
		return this->value < formula.value;
	}
};

