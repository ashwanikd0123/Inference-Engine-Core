#pragma once
#include <string>
#include <set>

#include "AtpVariable.h"

class AtpFunctor
{
public:
	int value;   
	std::string name;

	int arity;
	std::set<AtpVariable> variables;
	std::set<AtpFunctor> functors;

	bool operator==(const AtpFunctor& functor) const {
		if (this->arity != functor.arity ||
			this->variables.size() != functor.variables.size() ||
			this->functors.size() != functor.functors.size() ||
			std::strcmp(this->name.c_str(), functor.name.c_str()) != 0) {
			return false;
		}

		for (auto& v : this->variables) {
			if (functor.variables.find(v) == functor.variables.end()) {
				return false;
			}
		}

		for (auto& f : this->functors) {
			if (functor.functors.find(f) == functor.functors.end()) {
				return false;
			}
		}

		return true;
	}

	bool operator<(const AtpFunctor& functor) const {
		return this->value < functor.value;
	}
};

