#pragma once
#include "AtpClause.h"

enum AtpStatementType {
	AXIOM,
	CONJENCTURE
};

class AtpStatement
{
public:
	AtpStatementType type;
	std::string name;
	std::set<AtpClause> clauses;
	int value;

	// operator overloading
	bool operator==(const AtpStatement& statement) const
	{
		if (this->clauses.size() != statement.clauses.size()) {
			return false;
		}

		for (auto& clause : this->clauses) {
			if (statement.clauses.find(clause) == statement.clauses.end()) {
				return false;
			}
		}

		return true;
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

