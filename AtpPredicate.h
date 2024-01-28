#pragma once
#include "AtpTerm.h"

class AtpPredicate
{
public:
	int value;
	std::string name;

	std::set<AtpTerm> args;

	bool operator==(const AtpPredicate& predicate) const {
		if (predicate.args.size() != this->args.size()) {
			return false;
		}

		for (auto& arg : this->args) {
			if (predicate.args.find(arg) == predicate.args.end()) {
				return false;
			}
		}

		return std::strcmp(this->name.c_str(), predicate.name.c_str()) == 0;
	}

	bool operator<(const AtpPredicate& predicate) const {
		return this->value < predicate.value;
	}
};

