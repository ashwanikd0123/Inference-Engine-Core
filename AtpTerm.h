#pragma once
#include <functional>

enum AtpTermType {
	CONSTANT,
	VARIABLE
};

class AtpTerm
{
public:
	AtpTermType type;
	int value;

	// operator overloading
	bool operator ==(const AtpTerm& term) const
	{
		return this->value == term.value && this->type == term.type;
	}

	bool operator <(const AtpTerm& term) const 
	{
		return this->value < term.value;
	}

	bool operator >(const AtpTerm& term) const
	{
		return this->value > term.value;
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
