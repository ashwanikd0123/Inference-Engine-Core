#pragma once
#include <functional>
#include <string>

#include "AtpFunctor.h"
#include "AtpVariable.h"

enum AtpTermType {
	FUNCTOR,
	VARIABLE
};

class AtpTerm
{
public:
	int value;
	std::string name;

	AtpTermType type;
	AtpFunctor functor;
	AtpVariable variable;

	// operator overloading
	bool operator ==(const AtpTerm& term) const
	{
		if (this->value != term.value || this->type != term.type) {
			return false;
		}
		switch (this->type)
		{
		case FUNCTOR: return this->functor == term.functor;
		case VARIABLE: return this->variable == term.variable;
		}
		return false;
	}

	bool operator <(const AtpTerm& term) const 
	{
		return this->value < term.value;
	}
};

template <>
struct std::hash<AtpTerm>
{
	std::size_t operator()(const AtpTerm& term) const
	{
		return term.value;
	}
};
